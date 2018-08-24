#ifdef SOX_LADSPA_PLUGIN_HACK

#define PLUGIN_ID 3835
#define PLUGIN_NAME "hilbert_stereo_2000taps_soxhack"

#else

#define PLUGIN_ID 3832
#define PLUGIN_NAME "hilbert_stereo_2000taps"

#endif

#define D_SIZE 2048
#define NZEROS 2000
#define LATENCY 999

static float xcoeffs[] = {
5.09820089297683e-05f, 5.1095875513258e-05f, 5.12218184543419e-05f, 5.13599098027174e-05f, 5.15102217292164e-05f, 
5.16728265270849e-05f, 5.18477966132965e-05f, 5.20352045298997e-05f, 5.22351229454004e-05f, 5.24476246561796e-05f, 
5.26727825879464e-05f, 5.29106697972279e-05f, 5.31613594728955e-05f, 5.34249249377288e-05f, 5.37014396500167e-05f, 
5.39909772051979e-05f, 5.42936113375393e-05f, 5.46094159218544e-05f, 5.49384649752615e-05f, 5.52808326589831e-05f, 
5.56365932801854e-05f, 5.60058212938608e-05f, 5.63885913047516e-05f, 5.67849780693177e-05f, 5.71950564977472e-05f, 
5.76189016560116e-05f, 5.80565887679655e-05f, 5.85081932174926e-05f, 5.89737905506964e-05f, 5.94534564781395e-05f, 
5.99472668771291e-05f, 6.04552977940513e-05f, 6.09776254467539e-05f, 6.15143262269795e-05f, 6.20654767028479e-05f, 
6.26311536213906e-05f, 6.32114339111364e-05f, 6.38063946847502e-05f, 6.44161132417243e-05f, 6.50406670711244e-05f, 
6.56801338543905e-05f, 6.63345914681936e-05f, 6.70041179873485e-05f, 6.76887916877845e-05f, 6.83886910495738e-05f, 
6.91038947600196e-05f, 6.98344817168041e-05f, 7.05805310311965e-05f, 7.1342122031324e-05f, 7.21193342655049e-05f, 
7.29122475056453e-05f, 7.37209417507006e-05f, 7.45454972302022e-05f, 7.53859944078516e-05f, 7.62425139851813e-05f, 
7.7115136905284e-05f, 7.8003944356613e-05f, 7.89090177768513e-05f, 7.9830438856854e-05f, 8.07682895446627e-05f, 
8.17226520495944e-05f, 8.26936088464051e-05f, 8.36812426795299e-05f, 8.46856365674006e-05f, 8.57068738068421e-05f, 
8.67450379775478e-05f, 8.78002129466372e-05f, 8.88724828732953e-05f, 8.99619322134959e-05f, 9.10686457248094e-05f, 
9.2192708471297e-05f, 9.33342058284935e-05f, 9.44932234884775e-05f, 9.56698474650335e-05f, 9.68641640989049e-05f, 
9.80762600631403e-05f, 9.93062223685357e-05f, 0.000100554138369172f, 0.000101820095768049f, 0.000103104182622824f, 
0.000104406487351644f, 0.000105727098739086f, 0.000107066105942201f, 0.000108423598496659f, 0.00010979966632301f, 
0.00011119439973305f, 0.000112607889436292f, 0.000114040226546566f, 0.000115491502588714f, 0.00011696180950542f, 
0.000118451239664147f, 0.000119959885864199f, 0.000121487841343904f, 0.000123035199787927f, 0.000124602055334698f, 
0.000126188502583984f, 0.00012779463660458f, 0.00012942055294214f, 0.000131066347627141f, 0.000132732117182981f, 
0.00013441795863423f, 0.000136123969515006f, 0.00013785024787751f, 0.0001395968923007f, 0.000141364001899121f, 
0.000143151676331881f, 0.00014496001581179f, 0.000146789121114649f, 0.000148639093588704f, 0.000150510035164263f, 
0.00015240204836348f, 0.000154315236310301f, 0.000156249702740597f, 0.000158205552012452f, 0.000160182889116651f, 
0.000162181819687329f, 0.000164202450012819f, 0.000166244887046681f, 0.000168309238418924f, 0.000170395612447423f, 
0.000172504118149532f, 0.0001746348652539f, 0.000176787964212495f, 0.000178963526212829f, 0.000181161663190406f, 
0.000183382487841381f, 0.000185626113635436f, 0.000187892654828889f, 0.000190182226478026f, 0.000192494944452667f, 
0.000194830925449972f, 0.000197190287008482f, 0.000199573147522417f, 0.000201979626256211f, 0.000204409843359316f, 
0.000206863919881256f, 0.000209341977786953f, 0.000211844139972317f, 0.000214370530280115f, 0.000216921273516124f, 
0.000219496495465561f, 0.000222096322909809f, 0.000224720883643444f, 0.000227370306491555f, 0.000230044721327382f, 
0.000232744259090262f, 0.000235469051803897f, 0.00023821923259495f, 0.000240994935711974f, 0.000243796296544678f, 
0.000246623451643542f, 0.000249476538739785f, 0.00025235569676569f, 0.0002552610658753f, 0.000258192787465487f, 
0.000261151004197404f, 0.00026413586001832f, 0.000267147500183865f, 0.000270186071280671f, 0.000273251721249426f, 
0.000276344599408358f, 0.00027946485647714f, 0.000282612644601245f, 0.000285788117376739f, 0.000288991429875537f, 
0.000292222738671127f, 0.00029548220186477f, 0.000298769979112182f, 0.000302086231650721f, 0.000305431122327072f, 
0.000308804815625459f, 0.00031220747769638f, 0.00031563927638588f, 0.000319100381265381f, 0.000322590963662071f, 
0.00032611119668987f, 0.000329661255280981f, 0.000333241316218041f, 0.000336851558166888f, 0.000340492161709951f, 
0.000344163309380276f, 0.000347865185696216f, 0.000351597977196777f, 0.000355361872477651f, 0.000359157062227949f, 
0.000362983739267643f, 0.000366842098585735f, 0.000370732337379175f, 0.000374654655092535f, 0.000378609253458467f, 
0.000382596336538949f, 0.000386616110767349f, 0.000390668784991321f, 0.000394754570516549f, 0.000398873681151364f, 
0.000403026333252244f, 0.000407212745770233f, 0.000411433140298284f, 0.000415687741119554f, 0.000419976775256682f, 
0.00042430047252205f, 0.000428659065569076f, 0.000433052789944547f, 0.000437481884142016f, 0.000441946589656297f, 
0.00044644715103908f, 0.000450983815955688f, 0.000455556835243012f, 0.000460166462968639f, 0.000464812956491219f, 
0.000469496576522084f, 0.00047421758718816f, 0.000478976256096201f, 0.000483772854398373f, 0.000488607656859224f, 
0.000493480941924076f, 0.00049839299178887f, 0.000503344092471504f, 0.000508334533884692f, 0.000513364609910398f, 
0.000518434618475863f, 0.000523544861631289f, 0.000528695645629195f, 0.000533887281005514f, 0.000539120082662454f, 
0.000544394369953175f, 0.000549710466768339f, 0.000555068701624555f, 0.000560469407754802f, 0.000565912923200845f, 
0.000571399590907727f, 0.000576929758820369f, 0.000582503779982345f, 0.000588122012636881f, 0.000593784820330146f, 
0.000599492572016886f, 0.000605245642168465f, 0.000611044410883386f, 0.000616889264000342f, 0.000622780593213882f, 
0.000628718796192747f, 0.000634704276700962f, 0.000640737444721744f, 0.000646818716584319f, 0.000652948515093713f, 
0.000659127269663609f, 0.000665355416452341f, 0.000671633398502135f, 0.00067796166588166f, 0.000684340675832001f, 
0.000690770892916143f, 0.000697252789172059f, 0.000703786844269515f, 0.000710373545670692f, 0.000717013388794727f, 
0.000723706877186299f, 0.000730454522688362f, 0.000737256845619155f, 0.000744114374953604f, 0.000751027648509256f, 
0.000757997213136859f, 0.000765023624915742f, 0.000772107449354127f, 0.000779249261594518f, 0.000786449646624322f, 
0.000793709199491856f, 0.000801028525527903f, 0.000808408240572975f, 0.000815848971210474f, 0.000823351355005907f, 
0.000830916040752354f, 0.000838543688722386f, 0.000846234970926605f, 0.000853990571379043f, 0.000861811186369611f, 
0.000869697524743822f, 0.000877650308190019f, 0.000885670271534348f, 0.000893758163043702f, 0.000901914744736917f, 
0.000910140792704453f, 0.000918437097436856f, 0.000926804464162272f, 0.000935243713193299f, 0.000943755680283501f, 
0.000952341216993872f, 0.000961001191069602f, 0.000969736486827464f, 0.000978548005554184f, 0.000987436665916156f, 
0.000996403404380882f, 0.00100544917565053f, 0.00101457495310801f, 0.00102378172927603f, 0.00103307051628946f, 
0.0010424423463817f, 0.00105189827238519f, 0.00106143936824687f, 0.00107106672955893f, 0.00108078147410544f, 
0.00109058474242537f, 0.00110047769839269f, 0.00111046152981399f, 0.00112053744904442f, 0.00113070669362243f, 
0.00114097052692418f, 0.0011513302388381f, 0.00116178714646059f, 0.0011723425948134f, 0.00118299795758367f, 
0.00119375463788728f, 0.0012046140690566f, 0.00121557771545334f, 0.00122664707330759f, 0.00123782367158394f, 
0.00124910907287575f, 0.00126050487432871f, 0.00127201270859462f, 0.0012836342448168f, 0.00129537118964818f, 
0.00130722528830337f, 0.00131919832564616f, 0.00133129212731367f, 0.00134350856087873f, 0.00135584953705203f, 
0.00136831701092544f, 0.00138091298325849f, 0.00139363950180938f, 0.00140649866271273f, 0.0014194926119056f, 
0.00143262354660411f, 0.00144589371683252f, 0.00145930542700712f, 0.00147286103757714f, 0.00148656296672509f, 
0.00150041369212919f, 0.00151441575279034f, 0.00152857175092661f, 0.00154288435393797f, 0.00155735629644459f, 
0.00157199038240166f, 0.00158678948729429f, 0.001601756560416f, 0.00161689462723451f, 0.0016322067918488f, 
0.00164769623954154f, 0.00166336623943129f, 0.00167922014722896f, 0.00169526140810349f, 0.00171149355966163f, 
0.00172792023504739f, 0.00174454516616657f, 0.00176137218704254f, 0.00177840523730933f, 0.00179564836584877f, 
0.00181310573457861f, 0.00183078162239899f, 0.001848680429305f, 0.00186680668067369f, 0.00188516503173399f, 
0.0019037602722289f, 0.00192259733127966f, 0.00194168128246203f, 0.00196101734910576f, 0.00198061090982861f, 
0.0020004675043172f, 0.00202059283936774f, 0.00204099279520004f, 0.00206167343205984f, 0.00208264099712436f, 
0.00210390193172804f, 0.00212546287892535f, 0.00214733069140967f, 0.00216951243980758f, 0.00219201542136969f, 
0.00221484716908029f, 0.00223801546120942f, 0.00226152833133288f, 0.00228539407884685f, 0.0023096212800062f, 
0.00233421879951673f, 0.00235919580271455f, 0.00238456176836714f, 0.00241032650213372f, 0.00243650015072481f, 
0.00246309321680371f, 0.0024901165746756f, 0.00251758148681345f, 0.00254549962127302f, 0.00257388307005356f, 
0.00260274436846438f, 0.00263209651556236f, 0.00266195299573018f, 0.00269232780147f, 0.00272323545749352f, 
0.00275469104619514f, 0.00278671023460161f, 0.00281930930289935f, 0.00285250517464792f, 0.0028863154487972f, 
0.00292075843363528f, 0.00295585318280403f, 0.0029916195335311f, 0.00302807814723882f, 0.00306525055270442f, 
0.00310315919196057f, 0.00314182746914119f, 0.00318127980249571f, 0.00322154167981387f, 0.00326263971752515f, 
0.00330460172375999f, 0.00334745676568631f, 0.00339123524146327f, 0.00343596895718598f, 0.00348169120922976f, 
0.00352843687244122f, 0.00357624249466629f, 0.00362514639815303f, 0.00367518878841946f, 0.00372641187123577f, 
0.00377885997843517f, 0.00383257970334091f, 0.00388762004667766f, 0.00394403257392705f, 0.00400187158518796f, 
0.00406119429871691f, 0.00412206104945112f, 0.00418453550396096f, 0.00424868489344034f, 0.00431458026652584f, 
0.00438229676394192f, 0.00445191391720249f, 0.00452351597386361f, 0.00459719225212221f, 0.00467303752789694f, 
0.0047511524579165f, 0.00483164404278462f, 0.00491462613449919f, 0.00500021999348529f, 0.00508855490087103f, 
0.00517976883250538f, 0.00527400920210586f, 0.00537143368195195f, 0.00547221111073161f, 0.00557652249953325f, 
0.00568456214858891f, 0.00579653888925959f, 0.00591267746796149f, 0.00603322009132631f, 0.00615842815494468f, 
0.00628858418165422f, 0.00642399399961549f, 0.00656498919551321f, 0.00671192988429943f, 0.00686520784417725f, 
0.00702525007427895f, 0.00719252284305794f, 0.0073675363082184f, 0.0075508498045862f, 0.00774307791536794f, 
0.00794489746562636f, 0.00815705560564775f, 0.00838037918764792f, 0.00861578568385431f, 0.00886429594989741f, 
0.00912704920792227f, 0.00940532071324203f, 0.00970054268252728f, 0.0100143292083169f, 0.0103485060747437f, 
0.0107051466374756f, 0.0110866152573277f, 0.0114956202102992f, 0.0119352785772401f, 0.0124091964016752f, 
0.0129215684781149f, 0.0134773036182325f, 0.0140821833213544f, 0.0147430647250875f, 0.015468142956129f, 
0.0162672942044027f, 0.0171525300644814f, 0.0181386076512114f, 0.0192438615755633f, 0.02049135797565f, 
0.0219105260778214f, 0.0235395148960214f, 0.0254286811468366f, 0.0276458969463085f, 0.0302848904763518f, 
0.0334788544404882f, 0.0374236604883329f, 0.0424196451796691f, 0.0489519676076665f, 0.057858629883791f, 
0.0707225249359261f, 0.0909355662461271f, 0.127316728958984f, 0.212202255423423f, 0.636618327236149f, 
-0.636618327236149f, -0.212202255423423f, -0.127316728958984f, -0.0909355662461271f, -0.0707225249359261f, 
-0.057858629883791f, -0.0489519676076665f, -0.0424196451796691f, -0.0374236604883329f, -0.0334788544404882f, 
-0.0302848904763518f, -0.0276458969463085f, -0.0254286811468366f, -0.0235395148960214f, -0.0219105260778214f, 
-0.02049135797565f, -0.0192438615755633f, -0.0181386076512114f, -0.0171525300644814f, -0.0162672942044027f, 
-0.015468142956129f, -0.0147430647250875f, -0.0140821833213544f, -0.0134773036182325f, -0.0129215684781149f, 
-0.0124091964016752f, -0.0119352785772401f, -0.0114956202102992f, -0.0110866152573277f, -0.0107051466374756f, 
-0.0103485060747437f, -0.0100143292083169f, -0.00970054268252728f, -0.00940532071324203f, -0.00912704920792227f, 
-0.00886429594989741f, -0.00861578568385431f, -0.00838037918764792f, -0.00815705560564775f, -0.00794489746562636f, 
-0.00774307791536794f, -0.0075508498045862f, -0.0073675363082184f, -0.00719252284305794f, -0.00702525007427895f, 
-0.00686520784417725f, -0.00671192988429943f, -0.00656498919551321f, -0.00642399399961549f, -0.00628858418165422f, 
-0.00615842815494468f, -0.00603322009132631f, -0.00591267746796149f, -0.00579653888925959f, -0.00568456214858891f, 
-0.00557652249953325f, -0.00547221111073161f, -0.00537143368195195f, -0.00527400920210586f, -0.00517976883250538f, 
-0.00508855490087103f, -0.00500021999348529f, -0.00491462613449919f, -0.00483164404278462f, -0.0047511524579165f, 
-0.00467303752789694f, -0.00459719225212221f, -0.00452351597386361f, -0.00445191391720249f, -0.00438229676394192f, 
-0.00431458026652584f, -0.00424868489344034f, -0.00418453550396096f, -0.00412206104945112f, -0.00406119429871691f, 
-0.00400187158518796f, -0.00394403257392705f, -0.00388762004667766f, -0.00383257970334091f, -0.00377885997843517f, 
-0.00372641187123577f, -0.00367518878841946f, -0.00362514639815303f, -0.00357624249466629f, -0.00352843687244122f, 
-0.00348169120922976f, -0.00343596895718598f, -0.00339123524146326f, -0.00334745676568631f, -0.00330460172375999f, 
-0.00326263971752515f, -0.00322154167981387f, -0.00318127980249571f, -0.00314182746914119f, -0.00310315919196057f, 
-0.00306525055270442f, -0.00302807814723882f, -0.0029916195335311f, -0.00295585318280403f, -0.00292075843363528f, 
-0.0028863154487972f, -0.00285250517464792f, -0.00281930930289935f, -0.00278671023460161f, -0.00275469104619514f, 
-0.00272323545749352f, -0.00269232780147f, -0.00266195299573018f, -0.00263209651556236f, -0.00260274436846438f, 
-0.00257388307005356f, -0.00254549962127302f, -0.00251758148681345f, -0.0024901165746756f, -0.00246309321680371f, 
-0.00243650015072481f, -0.00241032650213372f, -0.00238456176836714f, -0.00235919580271455f, -0.00233421879951673f, 
-0.0023096212800062f, -0.00228539407884685f, -0.00226152833133288f, -0.00223801546120942f, -0.00221484716908029f, 
-0.00219201542136969f, -0.00216951243980758f, -0.00214733069140967f, -0.00212546287892535f, -0.00210390193172804f, 
-0.00208264099712436f, -0.00206167343205984f, -0.00204099279520004f, -0.00202059283936774f, -0.0020004675043172f, 
-0.00198061090982861f, -0.00196101734910576f, -0.00194168128246203f, -0.00192259733127966f, -0.0019037602722289f, 
-0.00188516503173399f, -0.00186680668067369f, -0.001848680429305f, -0.00183078162239899f, -0.00181310573457861f, 
-0.00179564836584877f, -0.00177840523730933f, -0.00176137218704254f, -0.00174454516616657f, -0.00172792023504739f, 
-0.00171149355966163f, -0.00169526140810349f, -0.00167922014722896f, -0.00166336623943129f, -0.00164769623954154f, 
-0.0016322067918488f, -0.00161689462723451f, -0.001601756560416f, -0.00158678948729429f, -0.00157199038240166f, 
-0.00155735629644459f, -0.00154288435393797f, -0.00152857175092661f, -0.00151441575279034f, -0.00150041369212919f, 
-0.00148656296672509f, -0.00147286103757714f, -0.00145930542700712f, -0.00144589371683252f, -0.00143262354660411f, 
-0.0014194926119056f, -0.00140649866271273f, -0.00139363950180938f, -0.00138091298325848f, -0.00136831701092544f, 
-0.00135584953705203f, -0.00134350856087873f, -0.00133129212731367f, -0.00131919832564616f, -0.00130722528830337f, 
-0.00129537118964818f, -0.0012836342448168f, -0.00127201270859462f, -0.00126050487432871f, -0.00124910907287575f, 
-0.00123782367158394f, -0.00122664707330759f, -0.00121557771545334f, -0.0012046140690566f, -0.00119375463788728f, 
-0.00118299795758367f, -0.0011723425948134f, -0.00116178714646059f, -0.0011513302388381f, -0.00114097052692418f, 
-0.00113070669362243f, -0.00112053744904442f, -0.00111046152981399f, -0.00110047769839269f, -0.00109058474242537f, 
-0.00108078147410544f, -0.00107106672955893f, -0.00106143936824687f, -0.00105189827238519f, -0.0010424423463817f, 
-0.00103307051628946f, -0.00102378172927603f, -0.00101457495310801f, -0.00100544917565053f, -0.000996403404380882f, 
-0.000987436665916155f, -0.000978548005554184f, -0.000969736486827464f, -0.000961001191069602f, -0.000952341216993872f, 
-0.000943755680283501f, -0.000935243713193299f, -0.000926804464162271f, -0.000918437097436856f, -0.000910140792704452f, 
-0.000901914744736917f, -0.000893758163043702f, -0.000885670271534348f, -0.000877650308190019f, -0.000869697524743822f, 
-0.000861811186369611f, -0.000853990571379043f, -0.000846234970926605f, -0.000838543688722386f, -0.000830916040752354f, 
-0.000823351355005906f, -0.000815848971210474f, -0.000808408240572975f, -0.000801028525527903f, -0.000793709199491856f, 
-0.000786449646624322f, -0.000779249261594518f, -0.000772107449354127f, -0.000765023624915742f, -0.000757997213136858f, 
-0.000751027648509256f, -0.000744114374953603f, -0.000737256845619155f, -0.000730454522688362f, -0.000723706877186299f, 
-0.000717013388794727f, -0.000710373545670692f, -0.000703786844269515f, -0.000697252789172059f, -0.000690770892916143f, 
-0.000684340675832001f, -0.000677961665881659f, -0.000671633398502135f, -0.000665355416452341f, -0.000659127269663609f, 
-0.000652948515093713f, -0.000646818716584319f, -0.000640737444721743f, -0.000634704276700962f, -0.000628718796192747f, 
-0.000622780593213882f, -0.000616889264000342f, -0.000611044410883386f, -0.000605245642168465f, -0.000599492572016885f, 
-0.000593784820330146f, -0.00058812201263688f, -0.000582503779982345f, -0.00057692975882037f, -0.000571399590907727f, 
-0.000565912923200845f, -0.000560469407754802f, -0.000555068701624555f, -0.000549710466768339f, -0.000544394369953175f, 
-0.000539120082662453f, -0.000533887281005514f, -0.000528695645629195f, -0.000523544861631289f, -0.000518434618475863f, 
-0.000513364609910398f, -0.000508334533884692f, -0.000503344092471504f, -0.00049839299178887f, -0.000493480941924075f, 
-0.000488607656859224f, -0.000483772854398373f, -0.000478976256096201f, -0.00047421758718816f, -0.000469496576522084f, 
-0.000464812956491219f, -0.000460166462968639f, -0.000455556835243012f, -0.000450983815955688f, -0.00044644715103908f, 
-0.000441946589656297f, -0.000437481884142016f, -0.000433052789944547f, -0.000428659065569076f, -0.00042430047252205f, 
-0.000419976775256681f, -0.000415687741119554f, -0.000411433140298284f, -0.000407212745770233f, -0.000403026333252244f, 
-0.000398873681151364f, -0.000394754570516549f, -0.00039066878499132f, -0.000386616110767349f, -0.000382596336538949f, 
-0.000378609253458467f, -0.000374654655092535f, -0.000370732337379175f, -0.000366842098585735f, -0.000362983739267643f, 
-0.000359157062227949f, -0.00035536187247765f, -0.000351597977196777f, -0.000347865185696216f, -0.000344163309380276f, 
-0.000340492161709951f, -0.000336851558166888f, -0.000333241316218041f, -0.000329661255280981f, -0.00032611119668987f, 
-0.000322590963662071f, -0.000319100381265381f, -0.00031563927638588f, -0.00031220747769638f, -0.00030880481562546f, 
-0.000305431122327072f, -0.000302086231650721f, -0.000298769979112182f, -0.00029548220186477f, -0.000292222738671127f, 
-0.000288991429875537f, -0.000285788117376739f, -0.000282612644601245f, -0.00027946485647714f, -0.000276344599408357f, 
-0.000273251721249426f, -0.000270186071280671f, -0.000267147500183865f, -0.00026413586001832f, -0.000261151004197404f, 
-0.000258192787465487f, -0.0002552610658753f, -0.00025235569676569f, -0.000249476538739785f, -0.000246623451643542f, 
-0.000243796296544678f, -0.000240994935711974f, -0.000238219232594951f, -0.000235469051803897f, -0.000232744259090262f, 
-0.000230044721327382f, -0.000227370306491555f, -0.000224720883643443f, -0.000222096322909809f, -0.00021949649546556f, 
-0.000216921273516124f, -0.000214370530280115f, -0.000211844139972316f, -0.000209341977786953f, -0.000206863919881256f, 
-0.000204409843359316f, -0.000201979626256211f, -0.000199573147522416f, -0.000197190287008482f, -0.000194830925449971f, 
-0.000192494944452667f, -0.000190182226478026f, -0.000187892654828889f, -0.000185626113635436f, -0.000183382487841381f, 
-0.000181161663190406f, -0.000178963526212829f, -0.000176787964212495f, -0.0001746348652539f, -0.000172504118149532f, 
-0.000170395612447423f, -0.000168309238418924f, -0.000166244887046681f, -0.000164202450012819f, -0.000162181819687329f, 
-0.000160182889116651f, -0.000158205552012452f, -0.000156249702740597f, -0.000154315236310301f, -0.00015240204836348f, 
-0.000150510035164263f, -0.000148639093588704f, -0.000146789121114649f, -0.00014496001581179f, -0.000143151676331881f, 
-0.000141364001899121f, -0.0001395968923007f, -0.00013785024787751f, -0.000136123969515006f, -0.00013441795863423f, 
-0.000132732117182981f, -0.000131066347627141f, -0.00012942055294214f, -0.00012779463660458f, -0.000126188502583984f, 
-0.000124602055334698f, -0.000123035199787927f, -0.000121487841343904f, -0.000119959885864199f, -0.000118451239664147f, 
-0.00011696180950542f, -0.000115491502588714f, -0.000114040226546566f, -0.000112607889436292f, -0.00011119439973305f, 
-0.00010979966632301f, -0.000108423598496659f, -0.000107066105942201f, -0.000105727098739086f, -0.000104406487351644f, 
-0.000103104182622824f, -0.000101820095768049f, -0.000100554138369172f, -9.93062223685357e-05f, -9.80762600631403e-05f, 
-9.68641640989048e-05f, -9.56698474650335e-05f, -9.44932234884776e-05f, -9.33342058284934e-05f, -9.2192708471297e-05f, 
-9.10686457248093e-05f, -8.9961932213496e-05f, -8.88724828732953e-05f, -8.78002129466372e-05f, -8.67450379775477e-05f, 
-8.57068738068421e-05f, -8.46856365674007e-05f, -8.36812426795298e-05f, -8.26936088464051e-05f, -8.17226520495944e-05f, 
-8.07682895446628e-05f, -7.9830438856854e-05f, -7.89090177768513e-05f, -7.80039443566129e-05f, -7.7115136905284e-05f, 
-7.62425139851813e-05f, -7.53859944078516e-05f, -7.45454972302022e-05f, -7.37209417507005e-05f, -7.29122475056453e-05f, 
-7.21193342655049e-05f, -7.1342122031324e-05f, -7.05805310311964e-05f, -6.98344817168041e-05f, -6.91038947600196e-05f, 
-6.83886910495737e-05f, -6.76887916877845e-05f, -6.70041179873485e-05f, -6.63345914681936e-05f, -6.56801338543904e-05f, 
-6.50406670711244e-05f, -6.44161132417243e-05f, -6.38063946847502e-05f, -6.32114339111364e-05f, -6.26311536213905e-05f, 
-6.20654767028479e-05f, -6.15143262269794e-05f, -6.09776254467539e-05f, -6.04552977940513e-05f, -5.99472668771291e-05f, 
-5.94534564781395e-05f, -5.89737905506963e-05f, -5.85081932174926e-05f, -5.80565887679655e-05f, -5.76189016560116e-05f, 
-5.71950564977472e-05f, -5.67849780693177e-05f, -5.63885913047516e-05f, -5.60058212938608e-05f, -5.56365932801854e-05f, 
-5.52808326589831e-05f, -5.49384649752615e-05f, -5.46094159218544e-05f, -5.42936113375393e-05f, -5.39909772051979e-05f, 
-5.37014396500167e-05f, -5.34249249377288e-05f, -5.31613594728955e-05f, -5.29106697972279e-05f, -5.26727825879464e-05f, 
-5.24476246561796e-05f, -5.22351229454004e-05f, -5.20352045298997e-05f, -5.18477966132965e-05f, -5.16728265270849e-05f, 
-5.15102217292164e-05f, -5.13599098027174e-05f, -5.12218184543419e-05f, -5.1095875513258e-05f, -5.09820089297683e-05f, 
};

