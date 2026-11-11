/*
 * one480 — MIT License
 * TR: Bu dosya MIT Lisansı kapsamında sunulur.
 * EN: This file is distributed under the MIT License.
 * Copyright (c) 2026 one480 contributors
 */
# one480

**Açık kaynaklı güvenlik tarayıcısı / Open-source security scanner**

> Bu proje eğitim ve araştırma amaçlıdır; ticari antivirüsün yerine geçmez. Yanlış pozitifler olabilir. Sezgisel göstergeler otomatik silme veya karantina tetiklemez.

## Özellikler
- Qt 6 Widgets tabanlı Türkçe masaüstü arayüzü.
- Dosya/klasör taraması, SHA-256 özeti ve EICAR test imzası kontrolü.
- Büyük dosyalar için güvenli boyut sınırı ve tarama iptali.
- Şüpheli çalıştırılabilir dosyalar yalnızca inceleme uyarısı üretir.
- Gerçek zamanlı izleme arayüzü için izleyici adaptörü.
- CLI ve C ABI çekirdek iskeleti.

## Build
Logo dosyanızı `pngs-jpgs-jpegs/logo.jpg` konumuna ekleyin. Logo olmadan CMake kasıtlı olarak durur.

```powershell
python -m pip install pillow
python tools/make_icon.py
cmake -S . -B build -G Ninja -DCMAKE_BUILD_TYPE=Release
cmake --build build --parallel
ctest --test-dir build --output-on-failure
```

Qt 6.5+, CMake 3.21+, C11/C++17 gerekir. Qt Windows DLL dağıtımı için `windeployqt` kullanılır.

## CLI
```text
one480-cli --scan <path>
```

## Güvenlik modeli
- Otomatik kalıcı silme yoktur.
- Kritik işletim sistemi yollarına müdahale edilmez.
- Bu kaynak sürümde karantina/geri yükleme ve gerçek zamanlı izleme UI seçenekleri bilgilendirme düzeyindedir; bunlar tam üretim koruması olarak sunulmaz.
- Gerçek zararlı yazılım örnekleri depoda bulunmaz; EICAR işareti testte bellekte kullanılır.

## Architecture
GUI -> Qt scanner adapter -> bounded file reads / digest -> result log.
C API and platform abstractions are isolated under `480/` and `hs/`.

## License
MIT. Qt 6 is dynamically linked and remains subject to its applicable LGPL/commercial licensing terms.
