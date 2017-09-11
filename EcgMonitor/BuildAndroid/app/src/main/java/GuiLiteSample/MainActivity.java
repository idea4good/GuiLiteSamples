package GuiLiteSample;

import android.content.DialogInterface;
import android.content.Intent;
import android.content.res.AssetManager;
import android.net.Uri;
import android.os.Environment;
import android.support.v7.app.AlertDialog;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.ImageView;

import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;

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
    }

    private void CopyAssetsToWorkFolder(String work_folder)
    {
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

    private void OpenHelpDialog()
    {
        AlertDialog.Builder builder = new AlertDialog.Builder(this);
        builder.setTitle("Help");
        builder.setMessage("Watch the video?");

        builder.setPositiveButton("Yes",
            new DialogInterface.OnClickListener() {
                @Override
                public void onClick(DialogInterface dialog,
                                    int which) {
                    Uri uri = Uri.parse("http://v.youku.com/v_show/id_XMjc2MjA4MDgzMg");
                    Intent intent = new Intent(Intent.ACTION_VIEW, uri);
                    startActivity(intent);
                }
            });

        builder.setNegativeButton("No",
            new DialogInterface.OnClickListener() {
                @Override
                public void onClick(DialogInterface dialog,
                                    int which) {
                }
        });

        ImageView img = new ImageView(this);
        img.setImageResource(R.drawable.help);
        builder.setView(img);

        builder.setCancelable(false).show();
    }

    private void Initialize() {
        if(ms_work_folder != null){
            return;
        }

        OpenHelpDialog();

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
    
    private static ThreadNative ms_thread_native = null;
    public static String ms_work_folder = null;
}
