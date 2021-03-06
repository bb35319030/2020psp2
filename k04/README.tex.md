# 課題4 レポート

bb35319030　西薗洸成

## 課題

[../sample/heights.csv]は標本全体（男性と女性合わせた14人）のデータをまとめたものである．
一方，[../sample/IDs.csv]は標本14人の学籍番号（身長データと同じ順番）である．
学籍番号を尋ねて，その学籍番号のデータがリストにあれば，学籍番号，身長，性別のデータを表示し，リストになければ，「No data」と表示せよ．

この二つのファイルを読み取り，学籍番号，身長，性別の3つをメンバーとする構造体の配列で管理するとよい．

## ソースコードの説明
1.7:構造体の配列を定義

1.26: データファイル名を入力させ，fnameに格納

1.27:入力させた文字列の最後にエンターキーが入っているので，fnameの文字列の最後をヌル文字'\0'に置換

l.28: fnameで指定したファイルの先頭アドレスをファイルポインタ fp に読み込む

l.30: もしfpがNULLだったときは，ファイルを開けなかったので，即座にプログラム終了

1.32: 一行目を空読みする

1.34:読み取ったファイルから性別と身長を14行分読み取る

1.38:ファイルを閉じる．閉じれないときは，即座にプログラム終了．

1.53:読み取ったファイルからIDを14行分読み取る

1.64:打ち込んだIDをbufに格納

1.65:bufをIDとして読み取る

1.68:IDがp[i].idと一致するときのiをtmpに代入

1.75:tmpが-1でないならIDを出力

1.77:genderが1ならMaleと出力

1.80:genderが1でないならFemaleと出力

1.83:身長を出力

1.86:tmpが-1のままなら”No data”と出力



## 入出力結果

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

ID 45313125のデータを調べたとき、
Input the filename of sample height :../sample/heights.csv
Input the filename of sample ID :../sample/IDs.csv
Which ID's data do you want? :45313125
---
ID: 45313125
gender: Female
height: 152.400000

ID 45313124のデータを調べたとき、
Input the filename of sample height :../sample/heights.csv
Input the filename of sample ID :../sample/IDs.csv
Which ID's data do you want? :45313124
---
No data
## 修正履歴

[comment #20200513]
- コーディングの原則として，「関数の中では数字は使わない」．代わりに`#define`を使う．ということで，
  - `#define Height 15`としているので，これを使って，関数の中の「15」とか「14」を表現してください．
- ちなみに，`define`している`Height`は何の値ですか．人数ならば`Height`という名前はそぐわないかもしれません．`N_Heights`とかのほうがいいかも．
　で，人数ならば15でなく14です．14に`define`して，関数中の15のところを「Height+1」にするのが素直と思います．
- `heights.csv`の1行目が単なるラベルだから，その1行分を増やして15にしたのかなと思われますが，これは結構問題があります．
  - `heights.csv`を読むfor文の中で，`sscanf(buf,"%d,%lf",...)`としていますが，このときbufに入っている1行にはアルファベットのラベルが書いてあって，intで読む整数やlfで読む実数が書かれていません．sscanfやscanfは，形式にあったものしか読み取りません．なので，1回目のforループでは，何も読み取られません．代入が起こらないから，おそらく初期値（変な値）のままになります．
- 1行読み飛ばすには，for文に入る直前に，fgetsだけを置くのが定石と思います．
- `#define Height 15`の意味は，Heightという変数に15を代入しているのではなく，コンパイル前に`Height`という文字列を`15`という文字列に書き換えるという意味です．なので，構造体の型名の別名定義したものが今`Height_t`ですが，この部分がコンパイル前に`15_t`になってしまいます．問題ですね．なので，defineで宣言する文字列は，関数の中に現れないような文字列にしないといけません．よくやるのが，すべて大文字にする．とか　`__Height__`のように記号ではさむとかです．工夫してください．

[comment #20200521]
- 理解がこんがらがってしまったようですね．
- ファイル読み込み，1行目を読み飛ばす，という処理の流れは，
  ```
  /* stdin（標準入力：キーボード）の長さsizeof(fname)だけをgetしてfnameに保存 */
  fgets(fname,sizeof(fname),stdin);
  /* ファイル名がfnameであるファイルのメモリ上のアドレスをfpに保存 */
  /* アドレスfpから始まるメモリにはファイルの中身がある */
  fp = fopen(fname,"r");
  /* fpのファイルの中身から1行分を何かに読み取る */
  /* （上のfgetsと使い方を比べてみてください．）*/
  /* lineという文字列に1行分保存する処理です */
  fgets(buf,sizeof(buf),fp);
  i=0;
  /* fgetsしてbufに1行読み込めたらばループ */
  while(fgets(buf,sizeof(buf),fp)){
    /* bufからscanf */
    sscanf(buf,"%d,%lf",&gender,&height);
    :
    i++:
  }
  ```
  もしwhileでなくforならば `i=0;`からの数行が
  ```
  /* i<N_HEIGHTならばループ */
  for(i=0;i<N_HEIGHT,i++){
    /* fgetsしてbufに1行読み込む */
    fgets(buf,sizeof(buf),fp);
    sscanf(buf,"%d,%lf",&gender,&height);
    :
  }
  ```
  となります．
  - sscanf(buf,"%d,%lf",...)をするために，bufに1行読み取っていないといけないですよね．
  

[comment 20200603]

課題提出お疲れさまでした。前回までの修正点を確認しました。とてもよくなっていると思います。k04は完了としますが気になる点が２つありました。
- 変数名として[tmp](L16)は使わない方がよいです。[IDnum]など意味が伝わるものにしましょう。
- 出力結果の[height: 152.400000]ですが答えは[height: 152.4]です。意味は同じですが、答えと全く同じ出力にするとより良いと思います。

以上です。報告する必要はありません、今後気を付けてもらえると良いと思います。お疲れさまでした！

[comment 20200624 kotaro]
- 課題4の完了を確認しました
