#!/usr/bin/env python3

import logging
import os


logger = logging.getLogger('rockgarden.binary_patch')
#logging.basicConfig()
#logger.setLevel(level=logging.DEBUG)  # uncomment to debuild patching compiler issues


from rockgarden import Patcher  # https://github.com/clach04/rockgarden/tree/diorite_pebble2_sdk43 - see https://github.com/cpfair/rockgarden/pull/2

pbw_filename_patch_list = [
    '589d536a6ca387c7de000052.pbw',  # 'pebble-send-message.pbw'  https://apps.rebble.io/en_US/application/56014a2508e93f4b6d000063?section=watchapps&dev_settings=true
    # Snowy?
]

p = Patcher()
for filename in pbw_filename_patch_list:
    filename_sans_ext, filename_ext = os.path.splitext(filename)
    filename_patched = filename_sans_ext + '-patched' + filename_ext
    print('Patching %s -> %s ...' %(filename, filename_patched))
    p.patch_pbw(filename,
                filename_patched,
                c_sources=["zero_punctuation.c"],
            )
