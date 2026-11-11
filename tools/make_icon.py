/*
 * one480 — MIT License
 * TR: Bu dosya MIT Lisansı kapsamında sunulur.
 * EN: This file is distributed under the MIT License.
 * Copyright (c) 2026 one480 contributors
 */
#!/usr/bin/env python3
"""Create app.ico from the user-supplied logo.jpg."""
from pathlib import Path
from PIL import Image
src=Path("pngs-jpgs-jpegs/logo.jpg")
if not src.is_file():
    raise SystemExit("ERROR: pngs-jpgs-jpegs/logo.jpg is missing. Add your own logo before building.")
im=Image.open(src).convert("RGBA")
im.save("resources/app.ico",format="ICO",sizes=[(16,16),(24,24),(32,32),(48,48),(64,64),(128,128),(256,256)])
