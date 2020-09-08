package com.guilite.hostmonitor;
import android.graphics.Bitmap;
import android.media.MediaPlayer;
import android.os.Build;
import android.util.Log;

import org.json.JSONArray;
import org.json.JSONObject;

import java.io.DataOutputStream;
import java.net.HttpURLConnection;
import java.net.URL;
import java.text.DateFormat;
import java.text.SimpleDateFormat;
import java.util.Calendar;

public class ThreadNative extends Thread {

    public void run() {
        OnSyncData(60, 98, 30, 120, 80, 100);//ping cloud
        startNative(UI_WIDHT, UI_HEIGHT, UI_COLOR_BYTES);
    }

    static public int on_action_down(int x, int y) {
        return sendTouch(true, x, y);
    }

    static public int on_action_up(int x, int y) {
        return sendTouch(false, x, y);
    }

    public static void OnPlayWav(String fileName) {
        if(ms_player == null) {
            return;
        }
        try {
            ms_player.stop();
            ms_player.reset();
            if(fileName != null) {
                ms_player.setDataSource(MainActivity.ms_work_folder + "heart_beat.wav");
            }
            ms_player.prepare();
            ms_player.start();
        }
        catch (Exception e) {
            Log.e("audio error", e.toString());
        }
    }

    public static void OnSyncData(int hr, int spo2, int rr, int nibp_sys, int nibp_dia, int nibp_mean){
        try {
            URL url = new URL("https://api.powerbi.com/beta/72f988bf-86f1-41af-91ab-2d7cd011db47/datasets/e0e71bab-d932-4bb8-bfcf-faec5aeadb60/rows?key=J9cQJK6rZyLYQ9NsuWV6RYyrgODk1Wu29tuzwMyBET62Xp1dxuJ5iR%2B0ZtL6o0ams029nNUhWci%2B%2B4GzxXHyBQ%3D%3D");
            HttpURLConnection conn = (HttpURLConnection) url.openConnection();
            conn.setRequestMethod("POST");
            //conn.setDoOutput(true);
            //conn.setDoInput(true);

            JSONObject jsonParam = new JSONObject();
            jsonParam.put("hr", hr);
            jsonParam.put("spo2", spo2);
            jsonParam.put("resp", rr);
            jsonParam.put("sys", nibp_sys);
            jsonParam.put("dia", nibp_dia);
            jsonParam.put("mean", nibp_mean);

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

            Log.d("JSON", raw_data.toString());
            Log.d("STATUS", String.valueOf(conn.getResponseCode()));
            Log.d("MSG" , conn.getResponseMessage());

            conn.disconnect();
        }catch (Exception e){
            e.printStackTrace();
        }
    }

    static private MediaPlayer ms_player = new MediaPlayer();

    native static public int onReceiveData(byte[] data, int length);
    native static public int updateBitmap(Bitmap bitmap, int width, int height);
    native static private int sendTouch(boolean is_down, int x, int y);
    native static private int startNative(int width, int height , int color_bytes);

    static public final int UI_WIDHT = 1024;
    static public final int UI_HEIGHT = 768;
    static public final int UI_COLOR_BYTES = 2;

    static {
        System.loadLibrary("native");
    }
}
