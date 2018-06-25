package gui_lite_sample;

import android.app.PendingIntent;
import android.hardware.usb.UsbConstants;
import android.hardware.usb.UsbDevice;
import android.hardware.usb.UsbDeviceConnection;
import android.hardware.usb.UsbEndpoint;
import android.hardware.usb.UsbInterface;
import android.hardware.usb.UsbManager;

import java.util.HashMap;
import java.util.Iterator;

public class UsbSerialCP210x {
    public String connect(UsbManager manager, PendingIntent permissionIntent, UsbReadCallback callback){
        this.callback = callback;

        HashMap<String, UsbDevice> deviceList = manager.getDeviceList();
        Iterator<UsbDevice> deviceIterator = deviceList.values().iterator();

        UsbDevice device;
        if (deviceIterator.hasNext()) {
            device = deviceIterator.next();
        }else{
            return "No device found!";
        }
        usbInterface = device.getInterface(0);
        if (usbInterface == null){
            return "No interface found!";
        }

        for (int i = 0; i < usbInterface.getEndpointCount(); i++){
            if(usbInterface.getEndpoint(i).getDirection() == UsbConstants.USB_DIR_OUT){
                endpointOut = usbInterface.getEndpoint(i);
            } else if (usbInterface.getEndpoint(i).getDirection() == UsbConstants.USB_DIR_IN){
                endpointIn = usbInterface.getEndpoint(i);
            }
        }

        manager.requestPermission(device, permissionIntent);
        if (false == manager.hasPermission(device)){
            return "No permission got!";
        }
        connection = manager.openDevice(device);
        connection.claimInterface(usbInterface, true);

        ReadThread thread = new ReadThread();
        thread.start();
        return device.toString() + "\n" + "Connection success";
    }

    public String send(byte[] data){
        if (null == endpointOut){
            return "No endpoint out!";
        }

        if (connection == null){
            return "No connection!";
        }
        int ret = connection.bulkTransfer(endpointOut, data, data.length, 0);
        return "Send: " + String.valueOf(ret) + " bytes";
    }

    public String setUsbCom(int baudRate)
    {
        if (connection == null){
            return "No connection!";
        }
        //Default setup
        int ret = connection.controlTransfer(0x41,0,1,0,
                null,0,0);
        if(ret < 0){
            return "Default setup failed!";
        }

        //Set baud rate
        byte[] data = new byte[] {
                (byte) (baudRate & 0xff),
                (byte) (baudRate >> 8 & 0xff),
                (byte) (baudRate >> 16 & 0xff),
                (byte) (baudRate >> 24 & 0xff) };

        ret = connection.controlTransfer(0x41,0x1E,0,0,
                data, data.length,0);
        if(ret < 0){
            return "Baud rate setup failed!";
        }
        return "Setup success";
    }

    public void releaseDevice(){
        connection.releaseInterface(usbInterface);
        connection.close();
        connection = null;
        usbInterface = null;
    }

    protected class ReadThread extends Thread{
        @Override
        public void run(){
            byte[] data = new byte[4096];
            while(true){
                try {
                    sleep(20);
                }catch (Exception e){
                }

                if(null == endpointIn){
                    continue;
                }

                int length = connection.bulkTransfer(endpointIn, data, data.length, 0);
                if (length > 0)
                {
                    callback.onReceive(data, length);
                }
            }
        }
    }

    protected UsbDeviceConnection connection = null;
    private UsbInterface usbInterface = null;
    private UsbEndpoint endpointIn = null;
    private UsbEndpoint endpointOut = null;
    private UsbReadCallback callback;
}

interface UsbReadCallback{
    void onReceive(final byte[] data, final int length);
}
