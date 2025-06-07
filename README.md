# Güçlü Parola Analizörü + 2FA (C++)

Bu proje, güçlü bir parola analizörü ve iki faktörlü kimlik doğrulama (2FA) sistemini C++ diliyle birleştiren bir konsol uygulamasıdır.

## ✨ Özellikler

* 🔐 Girilen parolanın güçlü olup olmadığını kontrol eder.
* 🔄 Rastgele güçlü parola üretir.
* 📲 6 haneli 2FA kodu oluşturur ve kullanıcıdan doğrulama ister.
* 📝 Tüm girişler `gunluk.txt` adlı dosyada zaman damgasıyla birlikte kaydedilir.

## 🚀 Kurulum ve Çalıştırma

### Derleme

// Windows (MinGW yüklü ise)
g++ main.cpp -o parolaUygulamasi.exe

### Çalıştırma

// Windows
./parolaUygulamasi.exe


## 📂 Dosyalar

* `main.cpp` → Uygulamanın kaynak kodu
* `gunluk.txt` → Uygulama çalışırken otomatik olarak oluşturulan deneme günlüğü

## 🔍 Kod Açıklaması

### Fonksiyonlar:

#### `gucluParolaMi(parola)`

Girilen parolanın şu kurallara göre güçlü olup olmadığını kontrol eder:

* En az 8 karakter
* En az bir küçük harf
* En az bir büyük harf
* En az bir rakam
* En az bir özel karakter (`@$!%*?&`)
  Bu kontrol, `regex` kullanılarak yapılır.

#### `gucluParolaOlustur(uzunluk)`

İstenilen uzunlukta (varsayılan 12) rastgele güçlü parola üretir. Büyük/küçük harf, rakam ve özel karakterler içeren bir karakter kümesi kullanır.

#### `ikiFAKoduUret()`

Sistem saati baz alınarak 6 basamaklı rastgele bir kod üretir. Bu kod, ikinci aşama doğrulama için kullanılır.

#### `ikiFADogrula(kod)`

Kullanıcıdan 2FA kodunu girmesini ister ve sistemin oluşturduğu kod ile eşleştirir. Başarılıysa erişime izin verir.

#### `denemeGirdisiYaz(durum)`

Tüm giriş denemeleri, işlem durumu ile birlikte `gunluk.txt` adlı dosyaya zaman damgası ile kaydedilir. Başarılı girişler, 2FA hataları ve zayıf parola uyarıları burada tutulur.

### `main()` Fonksiyonu:

Kullanıcıdan iki işlemden birini seçmesini ister:

1. Parola kontrolü ve 2FA
2. Rastgele güçlü parola oluşturma

* Eğer kullanıcı parola kontrolünü seçerse, önce parola kontrol edilir, ardından 2FA kodu oluşturularak doğrulama yapılır.
* Eğer güçlü parola oluşturma seçilirse, sistem otomatik olarak rastgele bir parola önerir.
* Her işlem sonucu günlüğe yazılır.

## 🔒 Güçlü Parola Kuralları

Bir parola aşağıdaki şartları sağlıyorsa **güçlü** kabul edilir:

* En az 8 karakter uzunluk
* En az bir küçük harf
* En az bir büyük harf
* En az bir rakam
* En az bir özel karakter (`@$!%*?&`)

## 👤 Yazar

Bu proje `İş Yeri Eğitimi` kapsamında Alim Salizov [230205930] tarafından geliştirilmiştir.

> Not: `gunluk.txt` dosyası uygulama çalıştığında aynı klasöre otomatik olarak oluşturulur.
