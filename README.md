# pebble_patch_tts

Patch Pebble smartwatch PBW binaries to remove punctuation from dictation/TTS and lower case

Latest version from https://github.com/clach04/pebble_patch_tts

Relies on the awesome rockgarden by Collin Fair.

NOTE use Python 3, tested with Python 3.5.2 and Pebble Tool v4.6-rc1 (active SDK: v4.3) with Send Message by Peter Summers https://apps.rebble.io/en_US/application/56014a2508e93f4b6d000063?section=watchapps&dev_settings=true


To get started:

    python3 -m pip install git+https://github.com/clach04/rockgarden.git

Then:

  1. Obtain the PBW files you want to patch.
  2. Edit to add the list of PBW file
  3. Run:

        python3 patch_tts_remove_punctuation.py

  4. Upload patched PBW to phone, e.g.:

        python -m http.server 8000

See https://rebble.io/2021/02/01/rebble-sideload-helper.html for sideloading information.

See https://developer.rebble.io/developer.pebble.com/guides/app-resources/platform-specific/index.html for platform information.

If the license is an issue for you, please contact me (and/or open an issue on GitHub).

