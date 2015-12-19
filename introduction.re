= イントロダクション

== TL;DR

 * 石川啄木の短歌に含まれる単語を意味ごとに分類し特徴量化
 * 特徴化された短歌をナイーブベイズで学習し分類器に
 * 完成した分類器をマルコフ連鎖で生成した短歌に適用し、最も「石川啄木らしい」短歌を選択する

== 能書き

おはようございます。タイトルに機械学習って入れればだいたいバズるだろみたいな
甘い考えで書き始めた博多市(hakatashi)です。いちおうSunProの会長ということになっています。
この会誌の編集長もしています。
自分で設定した締切当日にこれを書いてます。つらい。

さて、今回は技術島としてのコミケ初参加ですが、せっかくコミケに参加するんだから、
いつものガチガチの技術的なことではなく、少し趣を変えて文芸的なことをやりたいと思いました。
そこで、以前から暖めていたアイデアである「石川啄木の未完の短歌」と、
最近よく見る「機械学習」についての研究を記そうと思います。

機械学習といっても、結論から言うと、流行りの深層学習とかそういういうのではなく、
また人工知能やらにも応用しにくい内容ですが、
短歌に興味がある方も機械学習に興味がある方も、
どうか最後までお付き合いください。