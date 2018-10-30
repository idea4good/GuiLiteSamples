package gui_lite_sample;

import android.app.Dialog;
import android.app.PendingIntent;
import android.content.Context;
import android.content.Intent;
import android.content.res.AssetManager;
import android.hardware.usb.UsbManager;
import android.net.Uri;
import android.os.Build;
import android.os.Environment;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.view.Window;
import android.webkit.WebView;
import android.widget.Button;
import android.widget.Toast;

import org.json.JSONArray;
import org.json.JSONObject;

import java.io.DataOutputStream;
import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.net.HttpURLConnection;
import java.net.URL;
import java.text.DateFormat;
import java.text.SimpleDateFormat;
import java.util.Calendar;

public class MainActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        Initialize();
        if(null == ms_thread_native){
            ms_thread_native = new ThreadNative();
            ms_thread_native.start();
        }

        if(null == ms_manager){
            ms_manager = (UsbManager) getSystemService(Context.USB_SERVICE);
        }

        if (null == ms_permissionIntent){
            ms_permissionIntent = PendingIntent.getBroadcast(this, 0, new Intent("com.example.blyan.usbserial.USB_PERMISSION"), 0);
        }

        if (null == ms_cp210x){
            ms_cp210x = new UsbSerialCP210x();
        }
    }

    public void ChangeViewState() {
        View view_0 = findViewById(R.id.id_monitor_view_0);
        if(null == view_0){
            return;
        }

        if(View.GONE == view_0.getVisibility()){
            view_0.setVisibility(View.VISIBLE);
        }else{
            view_0.setVisibility(View.GONE);
        }

        ConnectUsbSerial();
    }

    private void CopyAssetsToWorkFolder(String work_folder) {
        AssetManager assetManager = getAssets();
        String[] files = null;
        try {
            files = assetManager.list("");
        } catch (IOException e) {
            Log.e("tag", "Failed to get asset file list.", e);
        }

        if (files == null){
            return;
        }

        for (String filename : files) {
            InputStream in = null;
            OutputStream out = null;
            try {
                in = assetManager.open(filename);
                File outFile = new File(work_folder, filename);
                out = new FileOutputStream(outFile);

                byte[] buffer = new byte[in.available()];
                int read;
                while((read = in.read(buffer)) != -1){
                    out.write(buffer, 0, read);
                }
            } catch(IOException e) {
                Log.e("tag", "Failed to copy asset file: " + filename, e);
            }
            finally {
                if (in != null) {
                    try {
                        in.close();
                    } catch (IOException e) {
                        Log.e("tag", "Failed to close InputStream", e);
                    }
                }
                if (out != null) {
                    try {
                        out.close();
                    } catch (IOException e) {
                        Log.e("tag", "Failed to close OutputStream", e);
                    }
                }
            }
        }
    }

    private void Initialize() {
        if(ms_work_folder != null){
            return;
        }

        new Thread(new Runnable() {
            @Override
            public void run() {
                SyncInfo();
            }
        }).start();

        showSourceCode();

        File folder = new File(Environment.getExternalStorageDirectory() + File.separator + "idea4good");
        ms_work_folder = folder.getPath() + File.separator;

        if(folder.exists()) {
            return;
        }

        if(folder.mkdirs()) {
            CopyAssetsToWorkFolder(ms_work_folder);
        } else {
            Log.e("tag", "Make work folder failed!");
        }
    }

    private void ConnectUsbSerial(){
        if(ms_cp210x.connection != null){
            return;
        }

        String ret = ms_cp210x.connect(ms_manager, ms_permissionIntent, new UsbReadCallback() {
            @Override
            public void onReceive(byte[] data, int length) {
                ThreadNative.OnReceiveData(data, length);
            }
        }) + "\n";
        ret += ms_cp210x.setUsbCom(9600);
        Toast.makeText(this, ret, Toast.LENGTH_LONG).show();
    }

    private void SyncInfo(){
        try {
            URL url = new URL("https://api.powerbi.com/beta/72f988bf-86f1-41af-91ab-2d7cd011db47/datasets/e0e71bab-d932-4bb8-bfcf-faec5aeadb60/rows?key=J9cQJK6rZyLYQ9NsuWV6RYyrgODk1Wu29tuzwMyBET62Xp1dxuJ5iR%2B0ZtL6o0ams029nNUhWci%2B%2B4GzxXHyBQ%3D%3D");
            HttpURLConnection conn = (HttpURLConnection) url.openConnection();
            conn.setRequestMethod("POST");
            //conn.setDoOutput(true);
            //conn.setDoInput(true);

            JSONObject jsonParam = new JSONObject();
            jsonParam.put("hr", 60);
            jsonParam.put("spo2", 98);
            jsonParam.put("resp", 30);
            jsonParam.put("sys", 120);
            jsonParam.put("dia", 80);
            jsonParam.put("mean", 100);

            DateFormat df = new SimpleDateFormat("yyyy-MM-dd'T'HH:mm:ss.SSSZ");
            String date = df.format(Calendar.getInstance().getTime());
            jsonParam.put("time", date);

            jsonParam.put("weight", 1);
            jsonParam.put("device_info", Build.MANUFACTURER + "-" + Build.MODEL);

            JSONArray raw_data = new JSONArray();
            raw_data.put(jsonParam);

            DataOutputStream os = new DataOutputStream(conn.getOutputStream());
            os.writeBytes(raw_data.toString());
            os.flush();
            os.close();

            Log.e("JSON", raw_data.toString());
            Log.e("STATUS", String.valueOf(conn.getResponseCode()));
            Log.e("MSG" , conn.getResponseMessage());

            conn.disconnect();
        }catch (Exception e){
            e.printStackTrace();
        }
    }

    private void showSourceCode(){
        sourceDialog= new Dialog(this);
        sourceDialog.requestWindowFeature(Window.FEATURE_NO_TITLE);
        sourceDialog.setContentView(R.layout.source_dialog);
        sourceDialog.setCancelable(true);
        sourceDialog.show();

        webView = (android.webkit.WebView)sourceDialog.findViewById(R.id.wb_webview);
        webView.setScrollbarFadingEnabled(false);
        webView.setHorizontalScrollBarEnabled(false);
        webView.getSettings().setJavaScriptEnabled(true);
        webView.loadUrl("https://github.com/idea4good/GuiLiteSamples/blob/master/doc/README-cn.md");


        buttonVideo = (Button) sourceDialog.findViewById(R.id.bt_watchVideo);
        buttonVideo.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Uri uri = Uri.parse("http://v.youku.com/v_show/id_XMzA5NTMzMTYyOA");
                Intent intent = new Intent(Intent.ACTION_VIEW, uri);
                startActivity(intent);
                sourceDialog.dismiss();
            }
        });
    }

    private static ThreadNative ms_thread_native = null;
    public static String ms_work_folder = null;

    private static UsbManager ms_manager = null;
    private static PendingIntent ms_permissionIntent = null;
    private static UsbSerialCP210x ms_cp210x = null;

    private Dialog sourceDialog;
    private WebView webView;
    private Button buttonVideo;
}
