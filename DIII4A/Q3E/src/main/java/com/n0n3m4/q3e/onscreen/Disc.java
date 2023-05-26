package com.n0n3m4.q3e.onscreen;

import android.graphics.Bitmap;
import android.graphics.Canvas;
import android.graphics.Paint;
import android.graphics.PorterDuffXfermode;
import android.graphics.RectF;
import android.view.View;

import com.n0n3m4.q3e.Q3EControlView;
import com.n0n3m4.q3e.gl.GL;

import java.nio.ByteBuffer;
import java.nio.ByteOrder;
import java.nio.FloatBuffer;

import javax.microedition.khronos.opengles.GL10;
import javax.microedition.khronos.opengles.GL11;

public class Disc extends Paintable implements TouchListener
{
    public static class Part
    {
        public float start;
        public float end;
        public char key;
        public int textureId;
        public int borderTextureId;
        public boolean pressed;
        public boolean disabled;
    }

    private final FloatBuffer m_fanVertexArray;
    float[] verts_back = {-0.5f, -0.5f, -0.5f, 0.5f, 0.5f, 0.5f, 0.5f, -0.5f};
    FloatBuffer verts_p;
    float[] texcoords = {0, 0, 0, 1, 1, 1, 1, 0};
    FloatBuffer tex_p;
    byte[] indices = {0, 1, 2, 0, 2, 3};
    ByteBuffer inds_p;
    private Part[] m_parts = null;
    public int size;
    int dot_size;
    public int cx, cy;
    int tex_ind;
    private int m_circleWidth;
    private final char[] m_keys;

    int dotx, doty;
    boolean dotjoyenabled = false;
    public View view;

    private Part GenPart(int index, char key, int total, GL10 gl)
    {
        Part res = new Part();
        res.key = key;
        double P = Math.PI * 2 / total;
        int centerR = size / 2;
        double start = P * index;
        double end = start + P;
        final double offset = -Math.PI / 2;
        final double mid = (end + start) / 2 + offset;
        int r = dot_size / 2;
        int sw = m_circleWidth / 2;
        final int fontSize = 10;

        Bitmap bmp = Bitmap.createBitmap(dot_size, dot_size, Bitmap.Config.ARGB_8888);
        Canvas c = new Canvas(bmp);
        Paint p = new Paint();
        p.setAntiAlias(true);
        p.setARGB(255, 255, 255, 255);
        c.drawARGB(0, 0, 0, 0);
        p.setStrokeWidth(sw);
        p.setTextSize(sw * fontSize * 3 / 2);
        p.setTextAlign(Paint.Align.CENTER);
        Paint.FontMetrics fontMetrics = p.getFontMetrics();
        float fontHeight = (fontMetrics.descent - fontMetrics.ascent) / 2 - fontMetrics.descent;

        double rad = start + offset;
        double x = Math.cos(rad);
        double y = Math.sin(rad);
        c.drawLine(r + (int) (x * centerR), r + (int) (y * centerR), r + (int) (x * r), r + (int) (y * r), p);
        rad = end + offset;
        x = Math.cos(rad);
        y = Math.sin(rad);
        c.drawLine(r + (int) (x * centerR), r + (int) (y * centerR), r + (int) (x * r), r + (int) (y * r), p);

        x = Math.cos(mid);
        y = Math.sin(mid);
        int mr = (r + centerR) / 2;
        c.drawText("" + Character.toUpperCase(key), r + (int) (x * mr), r + (int) (y * mr + (fontHeight)), p);

        res.textureId = GL.loadGLTexture(gl, bmp);
        bmp.recycle();

        res.start = rad2deg(start);
        res.end = rad2deg(end);

        sw = m_circleWidth;
        bmp = Bitmap.createBitmap(dot_size, dot_size, Bitmap.Config.ARGB_8888);
        c = new Canvas(bmp);
        p = new Paint();
        p.setAntiAlias(true);
        p.setARGB(255, 255, 255, 255);
        c.drawARGB(0, 0, 0, 0);
        p.setStrokeWidth(sw);
        p.setTextSize(sw * fontSize);
        p.setTextAlign(Paint.Align.CENTER);
        fontMetrics = p.getFontMetrics();
        fontHeight = (fontMetrics.descent - fontMetrics.ascent) / 2 - fontMetrics.descent;
        rad = start + offset;
        x = Math.cos(rad);
        y = Math.sin(rad);
        centerR -= m_circleWidth;
        c.drawLine(r + (int) (x * centerR), r + (int) (y * centerR), r + (int) (x * r), r + (int) (y * r), p);
        rad = end + offset;
        x = Math.cos(rad);
        y = Math.sin(rad);
        c.drawLine(r + (int) (x * centerR), r + (int) (y * centerR), r + (int) (x * r), r + (int) (y * r), p);

        x = Math.cos(mid);
        y = Math.sin(mid);
        mr = (r + centerR) / 2;
        c.drawText("" + Character.toUpperCase(key), r + (int) (x * mr), r + (int) (y * mr + (fontHeight)), p);

        p.setStyle(Paint.Style.STROKE);
        start = start / Math.PI * 180;
        end = end / Math.PI * 180;
        RectF rect = new RectF(dot_size / 2 - size / 2 + sw / 2, dot_size / 2 - size / 2 + sw / 2, dot_size / 2 + size / 2 - sw / 2, dot_size / 2 + size / 2 - sw / 2);
        c.drawArc(rect, (float) (start - 90), (float) (end - start), false, p);

        rect = new RectF(0 + sw / 2, 0 + sw / 2, dot_size - sw / 2, dot_size - sw / 2);
        c.drawArc(rect, (float) (start - 90), (float) (end - start), false, p);

        res.borderTextureId = GL.loadGLTexture(gl, bmp);
        bmp.recycle();

        return res;
    }

    public void Paint(GL11 gl)
    {
        //main paint
        super.Paint(gl);
        GL.DrawVerts(gl, tex_ind, 6, tex_p, verts_p, inds_p, 0, 0, red, green, blue, alpha);
        if (null == m_parts || m_parts.length == 0)
            return;

        if (dotjoyenabled)
        {
            for (Part p : m_parts)
            {
                //DrawVerts(gl, p.textureId, 6, tex_p, m_fanVertexArray, inds_p, 0, 0, red,green,blue,p.pressed ? (float)Math.max(alpha, 0.9) : (float)(Math.min(alpha, 0.1)));
                if (p.pressed)
                    GL.DrawVerts(gl, p.borderTextureId, 6, tex_p, m_fanVertexArray, inds_p, 0, 0, red, green, blue, alpha + (1.0f - alpha) * 0.5f);
                else
                    GL.DrawVerts(gl, p.textureId, 6, tex_p, m_fanVertexArray, inds_p, 0, 0, red, green, blue, alpha - (alpha * 0.5f));
            }
        }
    }

    public Disc(View vw, GL10 gl, int center_x, int center_y, int r, float a, char[] keys)
    {
        view = vw;
        cx = center_x;
        cy = center_y;
        size = r * 2;
        dot_size = size * 3;
        alpha = a;

        float[] tmp = new float[verts_back.length];
        for (int i = 0; i < verts_back.length; i += 2)
        {
            tmp[i] = verts_back[i] * size + cx;
            tmp[i + 1] = verts_back[i + 1] * size + cy;
        }

        verts_p = ByteBuffer.allocateDirect(4 * verts_back.length).order(ByteOrder.nativeOrder()).asFloatBuffer();
        verts_p.put(tmp);
        verts_p.position(0);

        inds_p = ByteBuffer.allocateDirect(indices.length);
        inds_p.put(indices);
        inds_p.position(0);

        tex_p = ByteBuffer.allocateDirect(4 * texcoords.length).order(ByteOrder.nativeOrder()).asFloatBuffer();
        tex_p.put(texcoords);
        tex_p.position(0);

        float[] tmp2 = new float[verts_back.length];
        for (int i = 0; i < verts_back.length; i += 2)
        {
            tmp2[i] = verts_back[i] * dot_size + cx;
            tmp2[i + 1] = verts_back[i + 1] * dot_size + cy;
        }

        m_fanVertexArray = ByteBuffer.allocateDirect(4 * verts_back.length).order(ByteOrder.nativeOrder()).asFloatBuffer();
        m_fanVertexArray.put(tmp2);
        m_fanVertexArray.position(0);

        m_keys = keys;
    }

    @Override
    public void loadtex(GL10 gl)
    {
        Bitmap bmp = Bitmap.createBitmap(size, size, Bitmap.Config.ARGB_8888);
        Canvas c = new Canvas(bmp);
        Paint p = new Paint();
        p.setARGB(255, 255, 255, 255);
        c.drawARGB(0, 0, 0, 0);
        c.drawCircle(size / 2, size / 2, size / 2, p);
        p.setXfermode(new PorterDuffXfermode(android.graphics.PorterDuff.Mode.CLEAR));
        int internalsize = (size / 2 * 7 / 8);
        c.drawCircle(size / 2, size / 2, internalsize, p);

        m_circleWidth = size / 2 - internalsize;
        tex_ind = GL.loadGLTexture(gl, bmp);
        bmp.recycle();

        if (null != m_keys && m_keys.length > 0)
        {
            m_parts = new Part[m_keys.length];
            for (int i = 0; i < m_keys.length; i++)
            {
                m_parts[i] = GenPart(i, m_keys[i], m_keys.length, gl);
            }
        }
    }

    @Override
    public boolean onTouchEvent(int x, int y, int act/* 1: Down, -1: Up */)
    {
        if (null == m_parts || m_parts.length == 0)
            return true;
        dotjoyenabled = true;
        dotx = x - cx;
        doty = y - cy;
        boolean inside = 4 * (dotx * dotx + doty * doty) <= size * size;

        switch (act)
        {
            case 1:
                if (inside)
                    dotjoyenabled = true;
                break;
            case -1:
                if (dotjoyenabled)
                {
                    if (!inside)
                    {
                        boolean has = false;
                        for (Part p : m_parts)
                        {
                            if (!has)
                            {
                                if (p.pressed)
                                {
                                    has = true;
                                    ((Q3EControlView) (view)).sendKeyEvent(true, p.key, 0);
                                    ((Q3EControlView) (view)).sendKeyEvent(false, p.key, 0);
                                }
                            }
                            p.pressed = false;
                        }
                    } else
                    {
                        for (Part p : m_parts)
                            p.pressed = false;
                    }
                }
                dotjoyenabled = false;
                break;
            case 0:
            default:
                if (dotjoyenabled)
                {
                    if (!inside)
                    {
                        float t = rad2deg(Math.atan2(doty, dotx) + Math.PI / 2);
                        boolean has = false;
                        for (Part p : m_parts)
                        {
                            boolean b = false;
                            if (!has)
                            {
                                if (t >= p.start && t < p.end)
                                {
                                    has = true;
                                    b = true;
                                }
                            }
                            p.pressed = b;
                        }
                    } else
                    {
                        for (Part p : m_parts)
                            p.pressed = false;
                    }
                }
                break;
        }
        return true;
    }

    @Override
    public boolean isInside(int x, int y)
    {
        return 4 * ((cx - x) * (cx - x) + (cy - y) * (cy - y)) <= size * size;
    }

    public static void Move(Disc target, Disc src)
    {
        target.tex_ind = src.tex_ind;
        target.m_parts = src.m_parts;
    }

    private static float rad2deg(double rad)
    {
        double deg = rad / Math.PI * 180.0;
        return FormatAngle((float) deg);
    }

    private static float FormatAngle(float deg)
    {
        while (deg > 360)
            deg -= 360;
        while (deg < 0)
            deg += 360.0;
        return deg;
    }
}
