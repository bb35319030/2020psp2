# 課題4 レポート

bb35319030　西薗洸成

## 課題

[../sample/heights.csv]は標本全体（男性と女性合わせた14人）のデータをまとめたものである．
一方，[../sample/IDs.csv]は標本14人の学籍番号（身長データと同じ順番）である．
学籍番号を尋ねて，その学籍番号のデータがリストにあれば，学籍番号，身長，性別のデータを表示し，リストになければ，「No data」と表示せよ．

この二つのファイルを読み取り，学籍番号，身長，性別の3つをメンバーとする構造体の配列で管理するとよい．

## ソースコードの説明
1.8:構造体の配列を定義

1.23: データファイル名を入力させ，fnameに格納

1.24:入力させた文字列の最後にエンターキーが入っているので，fnameの文字列の最後をヌル文字'\0'に置換

l.26: fnameで指定したファイルの先頭アドレスをファイルポインタ fp に読み込む

l.27: もしfpがNULLだったときは，ファイルを開けなかったので，即座にプログラム終了

1.31:読み取ったファイルから性別と身長を15行分読み取る

1.34:ファイルを閉じる．閉じれないときは，即座にプログラム終了．

1.48:読み取ったファイルからIDを14行分読み取る

1.58:打ち込んだIDをbufに格納

1.59:bufをIDとして読み取る

1.61:IDがp[i].idと一致するときのiをtmpに代入

1.69:tmpが0以上かつ１５より小さい数ならIDを出力

1.71:genderが1ならMaleと出力

1.75:genderが1でないならFemaleと出力

1.77:身長を出力

1.78:tmpが０より小さい、または１５以上の時”No data”と出力



## 入出力結果
45313125と出力したとき

Input the filename of sample height : ../sample/heights.csv
Input the filename of sample ID : ../sample/IDs.csv
Which ID's data do you want? : 45313125
---
No data

45313124と出力したとき

Input the filename of sample height : ../sample/heights.csv
Input the filename of sample ID : ../sample/IDs.csv
Which ID's data do you want? : 45313125
---
No data

例えば，ID 45313125のデータを調べたいとき，

```
Input the filename of sample height : ../sample/heights.csv
Input the filename of sample ID : ../sample/IDs.csv
Which ID's data do you want? : 45313125
---
ID : 45313125
gender : Female
height : 152.4
```

例えば，ID 45313124のデータを調べたいとき，

```
Input the filename of sample height : ../sample/heights.csv
Input the filename of sample ID : ../sample/IDs.csv
Which ID's data do you want? : 45313124
---
No data
```

## 修正履歴

[comment #20200513]
- コーディングの原則として，「関数の中では数字は使わない」．代わりに`#define`を使う．ということで，
  - `#define Height 15`としているので，これを使って，関数の中の「15」とか「14」を表現してください．
- ちなみに，`define`している`Height`は何の値ですか．人数ならば`Height`という名前はそぐわないかもしれません．`N_Heights`とかのほうがいいかも．
　で，人数ならば15でなく14です．14に`define`して，関数中の15のところを「Height+1」にするのが素直と思います．
- `heights.csv`の1行目が単なるラベルだから，その1行分を増やして15にしたのかなと思われますが，これは結構問題があります．
  - `heights.csv`を読むfor文の中で，`sscanf(buf,"%d,%lf",...)`としていますが，このときbufに入っている1行にはアルファベットのラベルが書いてあって，intで読む整数やlfで読む実数が書かれていません．sscanfやscanfは，形式にあったものしか読み取りません．なので，1回目のforループでは，何も読み取られません．代入が起こらないから，おそらく初期値（変な値）のままになります．
- 1行読み飛ばすには，for文に入る直前に，fgetsだけを置くのが定石と思います．

  
