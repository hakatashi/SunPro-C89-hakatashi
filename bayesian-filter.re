= ベイジアンフィルタを作る

ようやくタイトルにある機械学習の話に辿り着きました。

前章では短歌っぽい文章を一万首近く生成しましたが、
「啄木の歌集にある単語を使用していること」と、
「啄木らしい短歌であること」は全く別の話です。
また、与えられた初二句である「大跨に緣側を歩けば」との繋がりも考慮されていません。
そこで、機械学習を用いて「啄木らしい短歌」の特徴を判定するフィルターを作ります。

== ナイーブベイズとは

ナイーブベイズは、機械学習で用いられる分類器の中でも、
ベイズの定理を理論的背景に置いた分類器となっています。

このナイーブベイズ分類器のバックアップとなる理論は非常に巧妙かつ複雑で、
すでに多くの先達によって詳しく解説されているので本稿では特に説明しませんが、
とりあえずテキスト分類などで多く用いられる分類器だと考えてくだされば結構です。

ナイーブベイズを用いたテキスト分類機のことを、ベイジアンフィルタと呼び、
今回は「啄木の短歌である」か、「啄木の短歌ではない」かを判定する
ベイジアンフィルタを実装していきます。
