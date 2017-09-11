package noodle.ui.sample;
import android.graphics.Bitmap;
import android.media.MediaPlayer;

public class ThreadNative extends Thread {

    public void run()
    {
        start_native(MAX_MAIN_DISPLAY, MAX_SUB_DISPLAY);
    }

    static public int on_action_dwon(int x, int y, int display_id)
    {//Touch too early will make APP crash here.
        return WriteHidFifo(OUTMSG_LBUTTONDOWN, x, y, display_id);
    }

    static public int on_action_up(int x, int y, int display_id)
    {
        return WriteHidFifo(OUTMSG_LBUTTONUP, x, y, display_id);
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
        }
    }

    static private MediaPlayer ms_player = new MediaPlayer();

    native static public int GetBitmapWidth(int display_id);
    native static public int GetBitmapHeight(int display_id);
    native static public int UpdateBitmap(Bitmap bitmap, int display_id, int width, int height);
    native static private  int WriteHidFifo(int type, int x, int y, int display_id);
    native private int start_native(int main_cnt, int sub_cnt);

    static private final int OUTMSG_LBUTTONUP = 0x4600;
    static private final int OUTMSG_LBUTTONDOWN = 0x4700;
    static private final int MAX_MAIN_DISPLAY = 1;
    static private final int MAX_SUB_DISPLAY = 9;

    static {
        System.loadLibrary("native");
    }
}
