package gui_lite_sample;

import android.content.Context;
import android.graphics.Bitmap;
import android.graphics.Canvas;
import android.graphics.Matrix;
import android.util.AttributeSet;
import android.view.MotionEvent;
import android.view.SurfaceHolder;
import android.view.SurfaceView;
import java.io.IOException;

public class MonitorView extends SurfaceView implements SurfaceHolder.Callback{
    public MonitorView(Context context, AttributeSet attrs) {
        super(context, attrs);
        // TODO Auto-generated constructor stub
        m_holder = getHolder();
        m_holder.addCallback(this);
        m_activity = (MainActivity) context;
    }

    public MonitorView(Context context) {
        super(context);
        // TODO Auto-generated constructor stub
        m_holder = getHolder();
        m_holder.addCallback(this);
    }

    @Override
    public void surfaceChanged(SurfaceHolder m_holder, int format, int width,
                               int height) {
    }

    @Override
    public void surfaceCreated(SurfaceHolder holder) {
        Canvas canvas = holder.lockCanvas();
        if(canvas != null)holder.unlockCanvasAndPost(canvas);

        int id = getId();
        switch (id)
        {
            case R.id.id_monitor_view_0:
                m_display_id = 0;
                break;
            case R.id.id_monitor_view_1:
                m_display_id = 1;
                break;
            case R.id.id_monitor_view_2:
                m_display_id = 2;
                break;
            case R.id.id_monitor_view_3:
                m_display_id = 3;
                break;
            case R.id.id_monitor_view_4:
                m_display_id = 4;
                break;
            case R.id.id_monitor_view_5:
                m_display_id = 5;
                break;
            case R.id.id_monitor_view_6:
                m_display_id = 6;
                break;
            case R.id.id_monitor_view_7:
                m_display_id = 7;
                break;
            case R.id.id_monitor_view_8:
                m_display_id = 8;
                break;
        }

        m_thread_update = new ThreadUpdate(this);
        m_thread_update.start();
    }

    @Override
    public void surfaceDestroyed(SurfaceHolder m_holder) {
    }

    private void build_bmp() {
        m_bm_width = ThreadNative.GetBitmapWidth(m_display_id);
        m_bm_height = ThreadNative.GetBitmapHeight(m_display_id);
        if(0 >= m_bm_width || 0 >= m_bm_height)
        {
            return;
        }

        m_bmp = Bitmap.createBitmap(m_bm_width, m_bm_height, Bitmap.Config.RGB_565);

        float scaleWidth =((float)getWidth() / m_bm_width);
        float scaleHeight =((float)getHeight() / m_bm_height);

        if(scaleWidth == 1.0f && scaleHeight == 1.0f)
        {
            m_is_use_matrix = false;
        }

        m_matrix.reset();
        m_matrix.postScale(scaleWidth, scaleHeight);
    }

    private void on_fresh() throws IOException {
        if(null == m_holder){
            return;
        }
        if(null == m_bmp){
            build_bmp();
            return;
        }

        ThreadNative.UpdateBitmap(m_bmp, m_display_id, m_bm_width, m_bm_height);

        Canvas canvas = m_holder.lockCanvas();
        if(null == canvas){
            return;
        }
        if(m_is_use_matrix){
            canvas.drawBitmap(m_bmp, m_matrix,null);
        }else{
            canvas.drawBitmap(m_bmp, 0, 0, null);
        }
        if(null != canvas)m_holder.unlockCanvasAndPost(canvas);
    }

    @Override
    public boolean onTouchEvent(MotionEvent e) {
        int logic_x = x2logic((int)e.getX());
        int logic_y = y2logic((int)e.getY());

        switch (e.getAction())
        {
            case MotionEvent.ACTION_DOWN:
                checkDoubleClick(e);
                ThreadNative.on_action_dwon(logic_x, logic_y, m_display_id);
                break;
            case MotionEvent.ACTION_UP:
                ThreadNative.on_action_up(logic_x, logic_y, m_display_id);
                break;
            case MotionEvent.ACTION_MOVE:
                ThreadNative.on_action_dwon(logic_x, logic_y, m_display_id);
                break;
            case MotionEvent.ACTION_CANCEL:
                ThreadNative.on_action_up(logic_x, logic_y, m_display_id);
                break;
        }
        return true;
    }

    private int x2logic(int x){
        if(m_bm_width == getWidth())
        {
            return x;
        }
        if(m_is_use_matrix && 0 != getWidth())
        {
            return (x * m_bm_width / getWidth());
        }
        else
        {
            return -1;
        }
    }

    private int y2logic(int y){
        if(m_bm_height == getHeight())
        {
            return y;
        }
        if(m_is_use_matrix && 0 != getHeight())
        {
            return (y * m_bm_height / getHeight());
        }
        else if(m_bm_height > getHeight())
        {
            return y;
        }
        return -1;
    }

    private class ThreadUpdate extends Thread{
        ThreadUpdate(MonitorView main_view){
            m_main_view = main_view;
        }
        public void run(){
            while (true) {
                try {
                    m_main_view.on_fresh();
                } catch (Exception e) {
                    e.printStackTrace();
                }
            }
        }
        private MonitorView m_main_view;
    }

    private void checkDoubleClick(MotionEvent e)
    {
        if(e.getAction() != MotionEvent.ACTION_DOWN)
        {
            return;
        }
        long time = e.getEventTime();
        if(ms_click_time != 0) {
            if(time - ms_click_time < THRESHOLD_DOUBLE_CLICK){
                m_activity.ChangeViewState();
            }
        }
        ms_click_time = time;
    }

    private MainActivity        m_activity;
    private SurfaceHolder 	    m_holder;
    private Matrix              m_matrix = new Matrix();
    private ThreadUpdate        m_thread_update;
    private boolean			    m_is_use_matrix = true;
    private int                 m_display_id = 0;

    private int	                m_bm_width;
    private int	                m_bm_height;
    private Bitmap              m_bmp = null;

    private static long         ms_click_time = 0;
    private static final long   THRESHOLD_DOUBLE_CLICK = 300;
}
