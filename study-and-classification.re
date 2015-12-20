= 学習と分類

前章までで「最後の一首」復元のためのお膳立ては整いました。
いよいよ実際に学習と分類を行い「最後の一首」を確定させます。

== 分類用ダミーデータの生成

（この記事のような怪しいエントリのせいで）たまに忘れそうになりますが、
機械学習の本質は「分類器」です。
なので、啄木の短歌だけを学習機に渡して
「この短歌から啄木らしさを学習して結果を教えてくれ」というような注文は受け付けられません。
@<strong>{「啄木らしさ」を学習するためには「啄木でないデータ」が必要です。}

この「啄木でないデータ」に何を選択するかは、分類したい対象のデータに依存します。
例えば観潮楼歌会@<fn>{kanchoro}の詠歌のうち、どれが啄木のものかを推定したいのであれば、
同時期の明治の歌人の短歌を学習データとして用いるべきですし、
ある文献の中に引用されている啄木の短歌を抽出したいなら、
その時代の出版物全体を学習データとして用いるべきです。
（後者の場合、機械学習は限りなく不適切なアプローチですが）

今回の場合、分類したい対象のデータは、啄木の歌集からマルコフ連鎖で生成した文章です。
語彙や用語のたぐいは啄木のそれと一致していることが既に保証されているので、
「啄木の歌集に含まれる単語をランダムに拾ったデータ」を分類用のダミーデータとして生成することにしました。

もちろんそうして生成したデータに「啄木らしいデータ」が含まれていない保証はありませんが、
確率上「啄木らしくないデータ」のほうが圧倒的に多いと信じて突き進みます。

前章で抽出した啄木の短歌のbag-of-wordsから、ランダムに6～12個（実際の出現数から決めました）選択し、
それを特徴量化したダミーデータを10000首用意しました。

== 多項ナイーブベイズによる学習

さて、たったいま生成したダミーデータと、
前章で生成した啄木の短歌の特徴量データを分類するナイーブベイズ分類器を作成します。

使用したフレームワークは、機械学習をやってる人ならおなじみscikit-learnです。
評価する特徴量はアナログ値なので、多項ナイーブベイズ(GaussianNB)を選択。
あとは実装するだけなので細かいコードとかは前述したリポジトリのデータを参照してください。

まずは学習機自体の性能を評価します。
@<m>{\alpha}値を@<m>{10^\{-10\}}から@<m>{10^\{10\}}まで遷移させたときの3分割交差検定の結果は以下のとおり。

//list[cross-validation][3分割交差検定による学習機の評価]{
alpha=1.000000e-10: 0.520659
alpha=1.000000e-09: 0.520659
alpha=1.000000e-08: 0.520659
alpha=1.000000e-07: 0.520659
alpha=1.000000e-06: 0.520659
alpha=1.000000e-05: 0.520659
alpha=1.000000e-04: 0.520659
alpha=1.000000e-03: 0.520659
alpha=1.000000e-02: 0.520659
alpha=1.000000e-01: 0.520938
alpha=1.000000e+00: 0.520659
alpha=1.000000e+01: 0.524009
alpha=1.000000e+02: 0.562256
alpha=1.000000e+03: 0.802903
alpha=1.000000e+04: 0.929090
alpha=1.000000e+05: 0.933277
alpha=1.000000e+06: 0.933277
alpha=1.000000e+07: 0.933277
alpha=1.000000e+08: 0.933277
alpha=1.000000e+09: 0.933277
alpha=1.000000e+10: 0.933277
//}

@<m>{\alpha = 10^5}以上で高いスコアを出すことがわかります。以降では@<m>{\alpha = 10^5}としました。

//footnote[kanchoro][明治40年から3年間にわたって開催された、森鴎外が自宅の観潮楼に文人を招いて開催した歌会のこと。石川啄木も参加した。]