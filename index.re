= 機械学習で石川啄木の未完の短歌を完成させる

== TL;DR

 * 石川啄木の短歌に含まれる単語を意味ごとに分類し特徴量化
 * 特徴化された短歌をナイーブベイズで学習し分類器に
 * 完成した分類器をマルコフ連鎖で生成した短歌に適用し、最も「石川啄木らしい」短歌を選択する

== 能書き

おはようございます。いちおうSunProの会長ということになっている博多市(hakatashi)です。
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

== 石川啄木について

まずは機械学習云々の前に、ご存じの方も多いでしょうが、
今回の研究対象である石川啄木について簡単に触れておきます。

石川啄木（本名 石川一）は、明治期に活躍した日本の歌人です。
この頃知られている歌人の中でも、特に若くしてこの世を去った歌人であり、
明治45年、満26歳にて病死しました。
彼の晩年の友人である土岐善麿が、昭和55年、満94歳にして生を全うしたことを考えると、
そのあまりにも早すぎる死が際立ちます。

石川啄木は、岩手県に生まれ、宮沢賢治や金田一京助などの数々の文人を輩出した
旧制盛岡中学校に在籍しました。
現在知られている彼の作品は、主に新聞や同人誌などの歌壇に掲載された物が多く、
そのうち半分以上が歌集に収録されています。
啄木が生涯で著した歌集は、わずかに『一握の砂』と『悲しき玩具』の二集のみであり、
『一握の砂』は明治43年、
『悲しき玩具』は明治45年、先述した土岐善麿の手によって啄木の死の二ヶ月後に、
それぞれ出版されました。

彼の歌風は極めてストレートで、特に歌集『一握の砂』以降の歌作は、
自然主義的傾向から日常に去来する感情を素直な言葉で綴ったものが多く、
卑近ながらにして読む者をハッとさせるような驚きと共感を与えてくれます。
啄木といえば、現代的には彼の書いた赤裸々でスキャンダラスな「ローマ字日記」が
（いい意味でも悪い意味でも）通俗に知られていますが、
これも自らの感情を包み隠さず歌った啄木ならではの文章だと言えるでしょう。

僕が特に気に入っている作品をいくつか紹介しましょう。

//quote{
	@<ruby>{治,おさ}まれる世の@<ruby>{事無,ことな}さに
	@<br>{}
	@<ruby>{飽,あ}きたりといひし頃こそ
	@<br>{}
	かなしかりけれ

	「さばかりの事に死ぬるや」
	@<br>{}
	「さばかりの事に生くるや」
	@<br>{}
	@<ruby>{止,よ}せ止せ問答

	今までのことを
	@<br>{}
	みな嘘にしてみれど、
	@<br>{}
	心すこしも@<ruby>{慰,なぐさ}まざりき。

	古新聞！
	@<br>{}
	おやここにおれの歌の事を@<ruby>{賞,ほ}めて書いてあり、
	@<br>{}
	二三@<ruby>{行,ぎやう}なれど。
//}

啄木の歌には、いくつかの形式的な特徴があります。
これは機械学習によって「啄木の短歌」を生成する際に大いに考慮するべき特徴なので、
詳しく述べていきます。

まず何より重要なのは、それまでの短歌や和歌には無かった
「一首三行書き」のスタイルです。
啄木は新聞や同人誌などの文壇に投稿する際は、スタンダードな一行書きの形式で
掲載されることが多かったのですが、歌集に収録される短歌はすべて、
この「三行書き」のスタイルで記されています。
これは土岐善麿の第一歌集『NAKIWARAI』の「ローマ字一首三行書き」の影響を受けてのものだと言われており、
改行によって一息つくことによって伝統的な@<ruby>{寂,さび}にも似た美観が生まれるとともに、
見た目にもコンパクトにまとまった印象を受けます。

次に、三十一文字の定型に囚われない、大胆な字余りと句跨がりが特徴として挙げられます。
明治以降においてはこのような破調を得意とする歌人が多いのも事実ですが、
その中でも啄木は特に過激な部類に属し、一句に二音以上、歌全体で六音以上の字余りというのも
ざらに見られます。

最後に、句読点などの約物の多用と字下げによる表現が挙げられます。
この特徴は主に第二歌集『悲しき玩具』に見られ、
句読点の他に感嘆符、疑問符、ダッシュ、括弧類が散りばめられて、
短歌であるにもかかわらず、まるで散文のような読み応えを感じます。
字下げは『悲しき玩具』の後半百首程度から特に顕著になり、
三行書きと相まって読む者に極めて特殊な印象を与えます。

全体として、内容的にも形式的にも、これまでの短歌のスタイルから大きく外れながら、
優れた名歌を詠み続けた歌人として、彼の死から百年以上経った現代においても石川啄木は知られています。
僕も詩歌や短歌の類をこよなく愛していますが、その中でも啄木は歌人とくれば第一に挙げられるほど愛好しており、
昔から彼の全集や歌集を書棚に収集しています。
僕が好んでいるのは、何よりも彼の歌に見られる彼の繊細な美意識と、
それを時として過激な言葉で綴ったストレートな感情の吐露、
そして三行書きという新たな枠組みによって確立されたリズムの心地よさです。
完全に余談ですが、僕も文芸を愛するものとして、ときおり歌屑など詠んでみるものですが、
その際は彼に倣って「三行書き」のスタイルを順守するようにしています。

== 啄木、最後の一首

さて、本篇の題にある「未完の短歌」という言葉に訝しんだ方も多いでしょう。
「未完の小説」「未完の大作」という言葉はあれど、短歌において未完ということはほとんど無いはずです。
僅かに三十一文字の短歌を途中で書いたまま残しておくということが考えにくいため当然ですが、
こと啄木においてはこの「未完の短歌」というものが存在します。

26という歳で惜しまれつつも結核で夭逝した石川啄木ですが、
先述したとおり、彼の最後の歌集である『悲しき玩具』は彼の死の直後に出版されています。
これは啄木が死の直前に、「一握の砂以降」と題された直筆の大学ノートなどを歌稿として託していたもので、
このノートが彼の遺稿であると言えるでしょう。

手元にこのノートの複製原稿があるため参照しますが、
このノートには規則正しく一ページに三行書きの短歌が四首記載され、
余計な書き込みもない綺麗な原稿です。
そして、最後のページには次のように記されています。

//image[01][『悲しき玩具』最後のページ]{
	庭のそとを白き犬ゆけり。
	　ふりむきて、
	　犬を飼はむと妻にはかれる。
	　　○
	大跨に緣側を歩けば、
//}

ご覧のとおり、一ページ四首であるところが二首しか記されておらず、
最後の一首は初二句が一行に書かれているのみで、続きが記されていません。
通し番号で言えば193首目、何らかの理由で啄木はここで筆を断ち、
最後の一句は未完成のまま遺されたと言っていいでしょう。

この未完成の一首は、善麿の発行した『悲しき玩具』や、のちに出版された啄木の全集や歌集では単に無視され、
啄木研究家の間でも深く顧みられることはありませんでした。
そのため一般にはあまり知られていない事実ですが、
啄木にはこのように絶筆となった「未完の短歌」が存在します。

===[column] 『悲しき玩具』の筆跡

ちなみに、この未完の短歌を含むノートの最後の数ページですが、
明らかにそれ以前の部分と筆跡が異なります。
それまでのページは、全体的にやや扁平の行書体で書かれており、
仮名も現代のものとほぼ変わらず、今から読んでも非常に読みやすいものになっているのに対して、
こちらの数ページのほうは連綿が多く、変体仮名が用いられた女性的な筆跡であり、
多少の古文書学の知識がないと読みにくいものになっています。

この数ページに含まれる17首の短歌が、誰か別人が代筆したものか、
それとも啄木の自筆によるものか、もしそうだとしたらなぜ筆跡を変えたのか、
という問題は啄木研究者の間でも意見が分かれており、
特に定まった説明がありません。
いずれにせよこれらの短歌が啄木の作であるということに異論はないので、
今回はこれ以上深く触れないことにします。

これについては、特に最近の論文で、同筆説を掲げる湯澤比呂子氏の
『石川啄木の筆跡考 : 「悲しき玩具歌稿ノート」の筆跡について』に詳しく記されているので、
参照してください。
以下のURLからオープンアクセスで入手できます。

@<href>{http://ir.iwate-u.ac.jp/dspace/bitstream/10140/1760/3/erar-v60n2p133-146.pdf}
