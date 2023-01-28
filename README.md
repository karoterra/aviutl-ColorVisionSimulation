# AviUtl スクリプト - 色覚シミュレーションKR

自分と違う色覚を持つ人はどのように色が見えているのかシミュレーションする
[AviUtl](http://spring-fragrance.mints.ne.jp/aviutl/) スクリプトです。

## 注意事項

このスクリプトは、P型、D型、T型色覚の人はどのように色が見えているか一般的な色覚の人が体験するためのものです。
ただし、各色覚の人がどのように色が見えているか厳密にシミュレーションするものではありません。
あくまでも、どのような色が見えにくかったり見やすかったりするか確認する程度に留めてください。

## 導入方法

1. Microsoft Visual C++ 再頒布可能パッケージ (x86) をインストールしてください。
   - Visual Studio 2022 を含むものがインストールされていれば大丈夫です。
   - [サポートされている最新の Visual C++ 再頒布可能パッケージのダウンロード | Microsoft Learn](https://learn.microsoft.com/ja-jp/cpp/windows/latest-supported-vc-redist?view=msvc-170)
2. [Releases](https://github.com/karoterra/aviutl-ColorVisionSimulation/releases)
   から最新版の ZIP ファイルをダウンロードしてください。
3. ZIP ファイルを展開し、以下のファイルを AviUtl 拡張編集の `script` フォルダまたはその1つ下の階層に配置してください。
   - `KaroterraColorVisionSimulation.dll`
   - `色覚シミュレーションKR.anm`

## 使い方

お好きなオブジェクトにアニメーション効果「色覚シミュレーションKR」を適用してください。

- type: 色覚の種類
  - 0 -> 一般的な色覚。色の変化なし
  - 1 -> P型色覚(1型2色覚)
  - 2 -> D型色覚(2型2色覚)
  - 3 -> T型色覚(3型2色覚)
- severity: シミュレーションの程度
  - 0 -> 変化なし
  - 100 -> 完全に変化

## 更新履歴

更新履歴は [CHANGELOG](CHANGELOG.md) を参照してください。

## ライセンス

このソフトウェアは Unlicense ライセンスのもとで公開されます。
詳細は [LICENSE](LICENSE) を参照してください。
