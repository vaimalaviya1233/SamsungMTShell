# SamsungTTSSystemShell

This tool allows most Samsung devices to achieve a `system` shell (UID 1000). It was patched in OneUI 5.1, but will work on Android 13 running OneUI 5.0 or older. It should work as far back and Android 9.0 (and maybe earlier).

## Usage

1. Downgrade the TTS app to the version provided in this repo (this must be done after every reboot).  
    `adb install -d ./com.samsung.SMT_v3.0.02.2.apk`
2. Run this command to wait for the reverse shell:  
    `adb shell nc -l -p 9999`
3. Install and open the `SMT Shell` app.

## Licence & Origin

This project is a fork of [SMT-CVE-2019-16253](https://github.com/flankerhqd/vendor-android-cves/tree/master/SMT-CVE-2019-16253), created by flankerhqd (AKA flanker017). There is also a write-up by flanker [here](https://blog.flanker017.me/text-to-speech-speaks-pwned). Due to the original repo containing multiple unrelated projects, this fork's git history was rewritten using `git filter-repo` so that it only contains the relevant code (and no prebuilt artifacts).

This repo will continue to use the LGPL license that the original used when this fork was created.

### Changes from the original

Please see the git commit history for a comprehensive list of changes. In brief:

* Refactored nearly all the code
* Replaced the reverse shell implementation
* Updated dependencies and build system to latest versions  
