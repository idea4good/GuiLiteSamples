package com.guilite.hostmonitor;

import android.content.Context;
import android.graphics.Bitmap;
import android.graphics.Canvas;
import android.graphics.Matrix;
import android.util.AttributeSet;
import android.util.Log;
import android.view.MotionEvent;
import android.view.SurfaceHolder;
import android.view.SurfaceView;
import java.io.IOException;

import static android.content.ContentValues.TAG;

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
        m_thread_update = new ThreadUpdate(this);
        m_thread_update.start();
    }

    @Override
    public void surfaceDestroyed(SurfaceHolder m_holder) {
    }

    private void build_bmp() {
        m_bm_width = ThreadNative.UI_WIDHT;
        m_bm_height = ThreadNative.UI_HEIGHT;

        m_bmp = Bitmap.createBitmap(m_bm_width, m_bm_height, Bitmap.Config.RGB_565);

        float scaleWidth =((float)getWidth() / m_bm_width);
        float scaleHeight =((float)getHeight() / m_bm_height);

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
        ThreadNative.updateBitmap(m_bmp, m_bm_width, m_bm_height);
        Canvas canvas = m_holder.lockCanvas();
        if(null == canvas){
            return;
        }

        canvas.drawBitmap(m_bmp, m_matrix,null);
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
                ThreadNative.on_action_down(logic_x, logic_y);
                break;
            case MotionEvent.ACTION_UP:
            case MotionEvent.ACTION_CANCEL:
                ThreadNative.on_action_up(logic_x, logic_y);
                break;
            case MotionEvent.ACTION_MOVE:
                ThreadNative.on_action_down(logic_x, logic_y);
                break;
        }
        return true;
    }

    private int x2logic(int x){
        if(0 != getWidth())
        {
            return (x * m_bm_width / getWidth());
        }
        else
        {
            return -1;
        }
    }

    private int y2logic(int y){
        if(0 != getHeight())
        {
            return (y * m_bm_height / getHeight());
        }
        return -1;
    }

    private class ThreadUpdate extends Thread{
        ThreadUpdate(MonitorView main_view){
            m_view = main_view;
        }
        public void run(){
            while (true) {
                try {
                    m_view.on_fresh();
                } catch (Exception e) {
                    e.printStackTrace();
                }
            }
        }
        private MonitorView m_view;
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
                m_activity.ConnectUsbSerial();
            }
        }
        ms_click_time = time;
    }

    private MainActivity        m_activity;
    private SurfaceHolder 	    m_holder;
    private Matrix              m_matrix = new Matrix();
    private ThreadUpdate        m_thread_update;

    private int	                m_bm_width;
    private int	                m_bm_height;
    private Bitmap              m_bmp = null;

    private static long         ms_click_time = 0;
    private static final long   THRESHOLD_DOUBLE_CLICK = 300;
}
