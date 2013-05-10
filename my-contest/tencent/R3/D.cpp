#define FILEIO

#define INPUT "in"
#define OUTPUT "ou"

#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cctype>
#include <vector>
#include <cassert>
#include <cstdlib>
#include <iostream>
#include <cassert>

#define mp make_pair
#define pb push_back
#define foreach(i,T) for(__typeof(T.begin()) i = T.begin(); i != T.end(); ++i)
#define rep(i,n) for(int i = 1; i <= n; i++)
#define REP(i,l,r) for(int i = l; i <= r; i++)

using namespace std;

namespace Solve {
    const int MAXN = 1000000;
    const int MAXM = 50000;

    int prime[MAXN],e[MAXN],div_num[MAXN], fac[MAXN];           // e[i]表示第i个素数因子的个数  
    bool flag[MAXN];  
    void get_prime()
    {  
        int i,j,k;  
        memset(flag,false,sizeof(flag));  
        k=0;  div_num[1] = 1;
        for(i=2;i<MAXN;i++){  
            if(!flag[i]){                              
                prime[k++]=i;  
                fac[i] = i;
                e[i]=1;  
                div_num[i]=2;                       //素数的约数个数为2  
            }
            for(j=0;j<k&&(long long)i*prime[j]<MAXN;j++){  
                flag[i*prime[j]]=true;              
                fac[i * prime[j]] = prime[j];
                if(i%prime[j]==0){  
                    div_num[i*prime[j]]=div_num[i]/(e[i]+1)*(e[i]+2);  
                    e[i*prime[j]]=e[i]+1;  
                    break;  
                }  
                else{  
                    div_num[i*prime[j]]=div_num[i]*div_num[prime[j]];  
                    e[i * prime[j]]=1;
                }  
            }  
        }  
    }  

    typedef long long Int64;
    const Int64 inf = (1ll << 62);

    inline Int64 mul(Int64 a, Int64 b) {
        long double next = (long double) a * b;
        if (next > inf) return inf; else return a * b;
    }

    inline Int64 pow(Int64 a, int n) {
        Int64 ret = 1;
        for (int i = 1; i <= n; i++) {
            ret = mul(ret, a);
        }
        return ret;
    }

    typedef pair<Int64, int> PII;

    PII f[20][50000];

    PII Dfs(int u, int k) {
        if (k == 1) return mp(1ll, 0);
        if (f[u][k] != mp(-1ll, -1)) return f[u][k];
        PII &ret = f[u][k]; ret = mp(inf, 0);
        for (int i = 1; i * i <= k; i++) if (k % i == 0) {
            Int64 tmp = pow(prime[u], i - 1);
            if (tmp != inf && i != 1) {
                PII next = Dfs(u + 1, k / i);
                ret = min(ret, mp(mul(tmp, next.first), i - 1));
            }
            tmp = pow(prime[u], k / i - 1);
            if (tmp != inf && i != k) {
                PII next = Dfs(u + 1, i);
                ret = min(ret, mp(mul(tmp, next.first), k / i - 1));
            }
        }
        return ret;
    }

    int Ans1[50000], cnt = 0;

    Int64 A[50000];

    inline void solve(void) {
        get_prime(); memset(f, -1, sizeof f);
A[10000]=89828829090000ll;
A[10010]=99810760896000000ll;
A[10032]=6585298668748800ll;
A[10044]=316560054524313600ll;
A[10080]=6746328388800ll;
A[10098]=7456882316083200ll;
A[10120]=154948203970560000ll;
A[10125]=234558414090000ll;
A[10140]=9532946142720000ll;
A[10143]=283262386176000000ll;
A[10150]=3230221247447040000ll;
A[10164]=6620101488000000ll;
A[10192]=793945152000000ll;
A[10200]=395208253440000ll;
A[10206]=79228619870400ll;
A[10208]=1348669167359754240ll;
A[10240]=9637611984000ll;
A[10260]=695566526054400ll;
A[10290]=2753267517000000ll;
A[10296]=720267041894400ll;
A[10304]=4943039000739840ll;
A[10336]=960136545903575040ll;
A[10350]=16366271201280000ll;
A[10368]=8995104518400ll;
A[10374]=1173285679104000000ll;
A[10395]=467493586560000ll;
A[10400]=67044257280000ll;
A[10404]=494187928038604800ll;
A[10416]=333004732681420800ll;
A[10440]=64750920243609600ll;
A[10450]=255515547893760000ll;
A[10472]=60526642176000000ll;
A[10500]=208024656840000ll;
A[10530]=141286950604800ll;
A[10560]=15420179174400ll;
A[10584]=29038543934400ll;
A[10608]=14816922004684800ll;
A[10625]=116629353308160000ll;
A[10626]=2085841207296000000ll;
A[10640]=2032499589120000ll;
A[10647]=201658476096000000ll;
A[10648]=591080490000000000ll;
A[10692]=74568112819200ll;
A[10710]=2301506887680000ll;
A[10725]=43916734794240000ll;
A[10752]=9316358251200ll;
A[10764]=390469474005811200ll;
A[10773]=4787134326374400ll;
A[10780]=4004752752000000ll;
A[10800]=18552403069200ll;
A[10816]=3519018976112640ll;
A[10875]=3948048191324160000ll;
A[10880]=197378293432320ll;
A[10890]=2912844654720000ll;
A[10920]=222304642560000ll;
A[10935]=150117385017600ll;
A[10944]=400477696819200ll;
A[10962]=377078888477491200ll;
A[10976]=235702467000000ll;
A[11000]=302581319040000ll;
A[11016]=367104555417600ll;
A[11025]=1431699108840000ll;
A[11040]=2746132778188800ll;
A[11050]=574909982760960000ll;
A[11088]=42237882086400ll;
A[11115]=516245698805760000ll;
A[11136]=58584165934694400ll;
A[11160]=259003680974438400ll;
A[11172]=20922789888000000ll;
A[11178]=16075315268812800ll;
A[11200]=24094029960000ll;
A[11220]=16947459809280000ll;
A[11232]=47973890764800ll;
A[11250]=676080134730000ll;
A[11264]=25700298624000ll;
A[11270]=1261805174784000000ll;
A[11286]=29827529264332800ll;
A[11319]=166043210256000000ll;
A[11340]=41944563460800ll;
A[11368]=3060705263616000000ll;
A[11375]=65604011235840000ll;
A[11385]=917770131210240000ll;
A[11400]=1580833013760000ll;
A[11424]=386174921932800ll;
A[11440]=2572382292480000ll;
A[11466]=3596104512000000ll;
A[11475]=3324398837760000ll;
A[11484]=2776671815152435200ll;
A[11500]=72904298987520000ll;
A[11520]=13492656777600ll;
A[11550]=1762091210880000ll;
A[11560]=1764956885852160000ll;
A[11583]=6058716881817600ll;
A[11592]=9105598159257600ll;
A[11600]=231253286584320000ll;
A[11616]=488752635571200ll;
A[11628]=1976751712154419200ll;
A[11648]=111025290055680ll;
A[11662]=966069586944000000ll;
A[11664]=32982049900800ll;
A[11700]=271705674240000ll;
A[11704]=242106568704000000ll;
A[11718]=1508315553909964800ll;
A[11745]=544669505578598400ll;
A[11760]=65996690760000ll;
A[11776]=4210736926556160ll;
A[11781]=358503957504000000ll;
A[11830]=898296848064000000ll;
A[11856]=59267688018739200ll;
A[11858]=1222681820976000000ll;
A[11875]=466517413232640000ll;
A[11880]=51624078105600ll;
A[11900]=10252167045120000ll;
A[11904]=234336663738777600ll;
A[11907]=337764116289600ll;
A[11934]=67111940844748800ll;
A[11960]=1394533835735040000ll;
A[11968]=6256033735311360ll;
A[11970]=9206027550720000ll;
A[11979]=3501015210000000000ll;
A[12000]=42164552430000ll;
A[12005]=1255701777561000000ll;
A[12012]=26480405952000000ll;
A[12075]=555194276904960000ll;
A[12096]=20238985166400ll;
A[12100]=12975398916480000ll;
A[12144]=105364778699980800ll;
A[12150]=178264394708400ll;
A[12160]=789513173729280ll;
A[12168]=6482403377049600ll;
A[12180]=856997473812480000ll;
A[12240]=300358272614400ll;
A[12250]=13325814782280000ll;
A[12285]=1869974346240000ll;
A[12288]=18632716502400ll;
A[12312]=1468418221670400ll;
A[12320]=150849578880000ll;
A[12348]=955215261000000ll;
A[12350]=2299639931043840000ll;
A[12375]=2545242860160000ll;
A[12376]=544739779584000000ll;
A[12393]=4270005618278400ll;
A[12400]=925013146337280000ll;
A[12420]=11129064416870400ll;
A[12474]=317895638860800ll;
A[12480]=61680716697600ll;
A[12495]=216872764416000000ll;
A[12500]=6292745869410000ll;
A[12528]=136696387180953600ll;
A[12540]=67789839237120000ll;
A[12544]=43369253928000ll;
A[12555]=2178678022314393600ll;
A[12584]=2364321960000000000ll;
A[12600]=80662622040000ll;
A[12636]=298272451276800ll;
A[12650]=4088248766300160000ll;
A[12672]=35980418073600ll;
A[12675]=395250613148160000ll;
A[12705]=274479592464000000ll;
A[12740]=16019011008000000ll;
A[12750]=12530426388480000ll;
A[12768]=1544699687731200ll;
A[12800]=34936343442000ll;
A[12825]=13297595351040000ll;
A[12852]=1565024683622400ll;
A[12870]=11651378618880000ll;
A[12880]=32519993425920000ll;
A[12936]=1389404016000000ll;
A[12960]=26985313555200ll;
A[12992]=316354496047349760ll;
A[13000]=1210325276160000ll;
A[13020]=3427989895249920000ll;
A[13034]=3864278347776000000ll;
A[13041]=76594149221990400ll;
A[13050]=1047441356881920000ll;
A[13056]=328963822387200ll;
A[13068]=1980734365209600ll;
A[13090]=1596972174336000000ll;
A[13104]=168951528345600ll;
A[13122]=316914479481600ll;
A[13125]=19248399129960000ll;
A[13167]=1434015830016000000ll;
A[13200]=117327450240000ll;
A[13230]=496711935720000ll;
A[13248]=6407643149107200ll;
A[13260]=152527138283520000ll;
A[13300]=41008668180480000ll;
A[13312]=102801194496000ll;
A[13328]=12703122432000000ll;
A[13338]=268447763378995200ll;
A[13365]=600469540070400ll;
A[13376]=25024134941245440ll;
A[13377]=664172841024000000ll;
A[13392]=546785548723814400ll;
A[13440]=27949074753600ll;
A[13464]=11524272670310400ll;
A[13475]=410025070224000000ll;
A[13500]=262153521630000ll;
A[13520]=23151440632320000ll;
A[13524]=334764638208000000ll;
A[13552]=16077389328000000ll;
A[13600]=1072708116480000ll;
A[13608]=107191662177600ll;
A[13650]=7048364843520000ll;
A[13662]=477240468229324800ll;
A[13680]=1201433090457600ll;
A[13689]=54528451936358400ll;
A[13720]=4255049799000000ll;
A[13728]=1955010542284800ll;
A[13750]=23690337390720000ll;
A[13770]=2260591209676800ll;
A[13800]=25293328220160000ll;
A[13824]=32607253879200ll;
A[13832]=2178959118336000000ll;
A[13851]=17080022473113600ll;
A[13860]=611337767040000ll;
A[13872]=1200170682379468800ll;
A[13888]=1265417984189399040ll;
A[13920]=175752497804083200ll;
A[13923]=3226535617536000000ll;
A[13950]=4189765427527680000ll;
A[13965]=867491057664000000ll;
A[14000]=359315316360000ll;
A[14025]=702667756707840000ll;
A[14040]=206496312422400ll;
A[14080]=77100895872000ll;
A[14094]=1028820177204019200ll;
A[14112]=60716955499200ll;
A[14144]=56304303617802240ll;
A[14168]=3873705099264000000ll;
A[14175]=938233656360000ll;
A[14196]=238323653568000000ll;
A[14250]=50121705553920000ll;
A[14256]=131928199603200ll;
A[14280]=3556874280960000ll;
A[14300]=51901595665920000ll;
A[14336]=46581791256000ll;
A[14352]=948283008299827200ll;
A[14364]=6260098734489600ll;
A[14400]=48910880818800ll;
A[14406]=134910108333000000ll;
A[14490]=147296440811520000ll;
A[14520]=4501669011840000ll;
A[14553]=11687339664000000ll;
A[14560]=603398315520000ll;
A[14580]=167778253843200ll;
A[14592]=1315855289548800ll;
A[14616]=582758282192486400ll;
A[14625]=10180971440640000ll;
A[14688]=767582252236800ll;
A[14700]=1872221911560000ll;
A[14720]=12632210779668480ll;
A[14742]=1271582555443200ll;
A[14784]=138781612569600ll;
A[14820]=610108553134080000ll;
A[14848]=269487163299594240ll;
A[14850]=883043441280000ll;
A[14875]=1049664179773440000ll;
A[14880]=703009991216332800ll;
A[14896]=50812489728000000ll;
A[14904]=23494691546726400ll;
A[14960]=41158116679680000ll;
A[14976]=143921672294400ll;
A[14994]=57537672192000000ll;
A[15000]=988117119990000ll;
A[15015]=1097918369856000000ll;
A[15048]=46097090681241600ll;
A[15066]=4115280708816076800ll;
A[15092]=196232884848000000ll;
A[15120]=74209612276800ll;
A[15125]=1328481227525760000ll;
A[15147]=96939470109081600ll;
A[15180]=1084637427793920000ll;
A[15200]=4290832465920000ll;
A[15210]=104862407569920000ll;
A[15232]=1776404640890880ll;
A[15246]=72821116368000000ll;
A[15288]=5557616064000000ll;
A[15300]=4347290787840000ll;
A[15309]=1351056465158400ll;
A[15360]=55898149507200ll;
A[15390]=9042364838707200ll;
A[15400]=2723231871360000ll;
A[15435]=35792477721000000ll;
A[15444]=7922937460838400ll;
A[15456]=24715195003699200ll;
A[15488]=2248262123627520ll;
A[15525]=212761525616640000ll;
A[15552]=80955940665600ll;
A[15600]=469309800960000ll;
A[15624]=2331033128769945600ll;
A[15625]=813244863240810000ll;
A[15660]=712260122679705600ll;
A[15675]=2810671026831360000ll;
A[15680]=216846269640000ll;
A[15708]=423686495232000000ll;
A[15750]=2704320538920000ll;
A[15795]=2401878160281600ll;
A[15808]=225217214471208960ll;
A[15840]=107941254220800ll;
A[15872]=1077948653198376960ll;
A[15876]=377501071147200ll;
A[15912]=103718454032793600ll;
A[15925]=1640100280896000000ll;
A[15960]=14227497123840000ll;
A[15972]=4137563430000000000ll;
A[16000]=174681717210000ll;
A[16016]=64309557312000000ll;
A[16038]=1267657917926400ll;
A[16065]=29919589539840000ll;
A[16100]=656138690887680000ll;
A[16128]=65214507758400ll;
A[16146]=4295164214063923200ll;
A[16170]=44052280272000000ll;
A[16192]=400386159059927040ll;
A[16200]=241181239899600ll;
A[16224]=17595094880563200ll;
A[16240]=2081279579258880000ll;
A[16250]=94761349562880000ll;
A[16320]=986891467161600ll;
A[16335]=37866980511360000ll;
A[16380]=2445351068160000ll;
A[16384]=93163582512000ll;
A[16416]=3070329008947200ll;
A[16464]=1649917269000000ll;
A[16500]=3328394509440000ll;
A[16524]=4772359220428800ll;
A[16560]=19222929447321600ll;
A[16625]=4198656719093760000ll;
A[16632]=464616702950400ll;
A[16640]=308403583488000ll;
A[16660]=256304176128000000ll;
A[16704]=410089161542860800ll;
A[16720]=164632466718720000ll;
A[16740]=2849040490718822400ll;
A[16758]=230150688768000000ll;
A[16767]=273280359569817600ll;
A[16800]=168658209720000ll;
A[16830]=186422057902080000ll;
A[16848]=527712798412800ll;
A[16875]=11493362290410000ll;
A[16896]=149061732019200ll;
A[16900]=467114360993280000ll;
A[16929]=387757880436326400ll;
A[16940]=324384972912000000ll;
A[17000]=19365204418560000ll;
A[17010]=713057578833600ll;
A[17024]=7105618563563520ll;
A[17100]=17389163151360000ll;
A[17136]=2703224453529600ll;
A[17150]=333145369557000000ll;
A[17160]=18006676047360000ll;
A[17199]=46749358656000000ll;
A[17248]=3771239472000000ll;
A[17250]=801947288862720000ll;
A[17280]=97821761637600ll;
A[17325]=22907185741440000ll;
A[17388]=100161579751833600ll;
A[17400]=1618773006090240000ll;
A[17408]=1644819111936000ll;
A[17424]=3421268448998400ll;
A[17472]=555126450278400ll;
A[17496]=428766648710400ll;
A[17500]=25170983477640000ll;
A[17550]=3532173765120000ll;
A[17556]=1694745980928000000ll;
A[17600]=385504479360000ll;
A[17640]=725963598360000ll;
A[17664]=21053684632780800ll;
A[17680]=370423050117120000ll;
A[17784]=414873816131174400ll;
A[17820]=671113015372800ll;
A[17836]=784931539392000000ll;
A[17850]=112773837496320000ll;
A[17856]=1640356646171443200ll;
A[17901]=872455230981734400ll;
A[17920]=139745373768000ll;
A[17952]=31280168676556800ll;
A[17955]=119678358159360000ll;
A[18000]=463810076730000ll;
A[18018]=291284465472000000ll;
A[18032]=812999835648000000ll;
A[18144]=222628836830400ll;
A[18150]=142729388081280000ll;
A[18200]=10892927485440000ll;
A[18216]=737553450899865600ll;
A[18225]=3387023499459600ll;
A[18240]=3947565868646400ll;
A[18252]=71306437147545600ll;
A[18304]=8993048494510080ll;
A[18360]=3303940998758400ll;
A[18375]=173235592169640000ll;
A[18400]=68653319454720000ll;
A[18432]=130429015516800ll;
A[18468]=19089436881715200ll;
A[18480]=1055947052160000ll;
A[18496]=4560648593041981440ll;
A[18522]=12417798393000000ll;
A[18560]=808461489898782720ll;
A[18564]=3813178457088000000ll;
A[18620]=1025216704512000000ll;
A[18630]=144677837419315200ll;
A[18700]=830425530654720000ll;
A[18711]=5404225860633600ll;
A[18720]=431765016883200ll;
A[18750]=81805696302330000ll;
A[18792]=1503660258990489600ll;
A[18810]=745688231608320000ll;
A[18816]=251541672782400ll;
A[18900]=1048614086520000ll;
A[18928]=578786015808000000ll;
A[18954]=5070631671705600ll;
A[19000]=77460817674240000ll;
A[19008]=323823762662400ll;
A[19040]=9654373048320000ll;
A[19110]=176209121088000000ll;
A[19125]=162895543050240000ll;
A[19136]=3603475431539343360ll;
A[19152]=10812897814118400ll;
A[19200]=216605329340400ll;
A[19208]=208497440151000000ll;
A[19250]=213213036516480000ll;
A[19278]=20345320887091200ll;
A[19305]=151467922045440000ll;
A[19320]=227639953981440000ll;
A[19360]=12218815889280000ll;
A[19404]=15283444176000000ll;
A[19440]=296838449107200ll;
A[19456]=6579276447744000ll;
A[19488]=1581772480236748800ll;
A[19500]=13313578037760000ll;
A[19584]=2302746756710400ll;
A[19600]=3233837847240000ll;
A[19602]=25749546747724800ll;
A[19656]=1858466811801600ll;
A[19683]=6021375110150400ll;
A[19712]=693908062848000ll;
A[19760]=1481692200468480000ll;
A[19800]=1290601952640000ll;
A[19840]=3233845959595130880ll;
A[19845]=8444102907240000ll;
A[19872]=49125264143155200ll;
A[19890]=1677798521118720000ll;
A[19950]=451095349985280000ll;
A[19968]=596246928076800ll;
A[19992]=88921857024000000ll;
A[20000]=2066063069070000ll;
A[20007]=3489820923926937600ll;
A[20020]=1297539891648000000ll;
A[20064]=125120674706227200ll;
A[20160]=195643523275200ll;
A[20196]=126766999373414400ll;
A[20240]=2634119467499520000ll;
A[20250]=4456609867710000ll;
A[20280]=162060084426240000ll;
A[20286]=3682411020288000000ll;
A[20328]=112541725296000000ll;
A[20384]=15084957888000000ll;
A[20400]=7508956815360000ll;
A[20412]=1510004284588800ll;
A[20475]=91628742965760000ll;
A[20480]=279490747536000ll;
A[20520]=13215763995033600ll;
A[20580]=46805547789000000ll;
A[20592]=13685073795993600ll;
A[20608]=113689897017016320ll;
A[20625]=307974386079360000ll;
A[20655]=38430050564505600ll;
A[20700]=278226610421760000ll;
A[20736]=260858031033600ll;
A[20790]=7947390971520000ll;
A[20800]=1542017917440000ll;
A[20880]=1230267484628582400ll;
A[20900]=3321702122618880000ll;
A[20944]=1028952916992000000ll;
A[21000]=3952468479960000ll;
A[21060]=2684452061491200ll;
A[21120]=447185196057600ll;
A[21168]=667886510491200ll;
A[21216]=281521518089011200ll;
A[21250]=1516181593006080000ll;
A[21280]=38617492193280000ll;
A[21294]=2621560189248000000ll;
A[21375]=651582172200960000ll;
A[21384]=1715066594841600ll;
A[21420]=39125617090560000ll;
A[21450]=570917552325120000ll;
A[21504]=288807105787200ll;
A[21546]=81381283548364800ll;
A[21560]=68080796784000000ll;
A[21600]=538019689006800ll;
A[21609]=1753831408329000000ll;
A[21632]=80937436450590720ll;
A[21735]=1914853730549760000ll;
A[21760]=4934457335808000ll;
A[21780]=49518359130240000ll;
A[21840]=4223788208640000ll;
A[21870]=2852230315334400ll;
A[21875]=3252979452963240000ll;
A[21888]=9210987026841600ll;
A[21952]=5421156741000000ll;
A[22000]=5749045061760000ll;
A[22032]=8443404774604800ll;
A[22050]=24338884850280000ll;
A[22080]=63161053898342400ll;
A[22113]=21616903442534400ll;
A[22176]=971471287987200ll;
A[22272]=1347435816497971200ll;
A[22275]=15011738501760000ll;
A[22344]=355687428096000000ll;
A[22356]=305430990107443200ll;
A[22400]=698726868840000ll;
A[22440]=288106816757760000ll;
A[22464]=1295295050649600ll;
A[22491]=747989738496000000ll;
A[22500]=12845522559870000ll;
A[22528]=745308660096000ll;
A[22572]=507067997493657600ll;
A[22638]=2158561733328000000ll;
A[22680]=964724959598400ll;
A[22750]=852852146065920000ll;
A[22800]=30035827261440000ll;
A[22815]=1363211298408960000ll;
A[22848]=8882023204454400ll;
A[22869]=946674512784000000ll;
A[22880]=48875263557120000ll;
A[22932]=61133776704000000ll;
A[22950]=56514780241920000ll;
A[23000]=1239373082787840000ll;
A[23040]=391287046550400ll;
A[23085]=153720202258022400ll;
A[23100]=29955550584960000ll;
A[23166]=102998186990899200ll;
A[23184]=173006365025894400ll;
A[23200]=4393812445102080000ll;
A[23232]=11241310618137600ll;
A[23296]=2775632251392000ll;
A[23328]=890515347321600ll;
A[23400]=5162407810560000ll;
A[23408]=4115811667968000000ll;
A[23520]=1517923887480000ll;
A[23552]=105268423163904000ll;
A[23625]=45973449161640000ll;
A[23712]=1126086072356044800ll;
A[23760]=1187353796428800ll;
A[23800]=174286839767040000ll;
A[23814]=6417518209502400ll;
A[23868]=1140902994360729600ll;
A[23936]=143888775912161280ll;
A[23940]=156502468362240000ll;
A[24000]=1222772020470000ll;
A[24024]=450166901184000000ll;
A[24057]=24085500440601600ll;
A[24192]=586930569825600ll;
A[24200]=220581781580160000ll;
A[24255]=572679643536000000ll;
A[24288]=2001930795299635200ll;
A[24300]=4100081078293200ll;
A[24320]=19737829343232000ll;
A[24336]=123165664163942400ll;
A[24375]=1231897544317440000ll;
A[24480]=6908240270131200ll;
A[24500]=226538851298760000ll;
A[24570]=31789563886080000ll;
A[24576]=577614211574400ll;
A[24624]=33773619098419200ll;
A[24640]=3469540314240000ll;
A[24696]=18149089959000000ll;
A[24750]=43269128622720000ll;
A[24786]=81130106747289600ll;
A[24840]=211452223920537600ll;
A[24948]=6040017138355200ll;
A[24960]=1788740784230400ll;
A[24990]=2819345937408000000ll;
A[25000]=119562171518790000ll;
A[25056]=3144016905161932800ll;
A[25080]=1152427267031040000ll;
A[25088]=1257708363912000ll;
A[25137]=2991958953984000000ll;
A[25200]=1855240306920000ll;
A[25245]=2423486752727040000ll;
A[25272]=6860266379366400ll;
A[25344]=1043432124134400ll;
A[25410]=3568234702032000000ll;
A[25480]=272323187136000000ll;
A[25500]=213017248604160000ll;
A[25515]=13548093997838400ll;
A[25536]=35528092817817600ll;
A[25600]=1083026646702000ll;
A[25650]=226059120967680000ll;
A[25704]=29735468988825600ll;
A[25725]=4330889804241000000ll;
A[25740]=198073436520960000ll;
A[25760]=617879875092480000ll;
A[25872]=26398676304000000ll;
A[25920]=782574093100800ll;
A[26000]=22996180247040000ll;
A[26082]=1302100536773836800ll;
A[26112]=9539950849228800ll;
A[26136]=37633952938982400ll;
A[26208]=3885885151948800ll;
A[26244]=7289033028076800ll;
A[26250]=327222785209320000ll;
A[26325]=60046954007040000ll;
A[26400]=2698531355520000ll;
A[26460]=9437526778680000ll;
A[26496]=147375792429465600ll;
A[26520]=2592961350819840000ll;
A[26600]=697147359068160000ll;
A[26624]=2981234640384000ll;
A[26656]=241359326208000000ll;
A[26676]=4563611977442918400ll;
A[26730]=11408921261337600ll;
A[26752]=575555103648645120ll;
A[26775]=1466059887452160000ll;
A[26880]=866421317361600ll;
A[26928]=218961180735897600ll;
A[27000]=6029530997490000ll;
A[27027]=3786698051136000000ll;
A[27040]=439877372014080000ll;
A[27104]=305470397232000000ll;
A[27200]=24672286679040000ll;
A[27216]=2671546041964800ll;
A[27225]=1855482045056640000ll;
A[27300]=119822202339840000ll;
A[27360]=27632961080524800ll;
A[27378]=926983682918092800ll;
A[27440]=80845946181000000ll;
A[27456]=44965242472550400ll;
A[27500]=402735735642240000ll;
A[27540]=42951232983859200ll;
A[27600]=480573236183040000ll;
A[27648]=1010824870255200ll;
A[27702]=324520426989158400ll;
A[27720]=11615417573760000ll;
A[27783]=211102572681000000ll;
A[27840]=4042307449493913600ll;
A[27945]=2459523236128358400ll;
A[28000]=8264252276280000ll;
A[28080]=4749415185715200ll;
A[28125]=1390696837139610000ll;
A[28160]=2235925980288000ll;
A[28224]=1760791709476800ll;
A[28288]=1294998983209451520ll;
A[28350]=17826439470840000ll;
A[28392]=4051502110656000000ll;
A[28431]=96342001762406400ll;
A[28500]=852068994416640000ll;
A[28512]=3562061389286400ll;
A[28560]=67580611338240000ll;
A[28600]=882327126320640000ll;
A[28665]=2290718574144000000ll;
A[28672]=1444035528936000ll;
A[28728]=118941875955302400ll;
A[28800]=1516237305382800ll;
A[28812]=2293471841661000000ll;
A[28875]=2771769474714240000ll;
A[28917]=345870455080550400ll;
A[28980]=2504039493795840000ll;
A[29040]=85531711224960000ll;
A[29106]=198684774288000000ll;
A[29120]=13878161256960000ll;
A[29160]=3858899838393600ll;
A[29184]=38159803396915200ll;
A[29250]=173076514490880000ll;
A[29376]=20724720810393600ll;
A[29400]=35572216319640000ll;
A[29403]=437742294711321600ll;
A[29440]=315805269491712000ll;
A[29484]=24160068553420800ll;
A[29568]=4024666764518400ll;
A[29700]=16777825384320000ll;
A[29792]=965437304832000000ll;
A[29808]=540377905574707200ll;
A[29920]=782004216913920000ll;
A[29952]=4173728496537600ll;
A[29988]=978140427264000000ll;
A[30000]=22726693759770000ll;
A[30096]=875844722943590400ll;
A[30184]=3335959042416000000ll;
A[30240]=2152078756027200ll;
A[30294]=1647970991854387200ll;
A[30375]=84675587486490000ll;
A[30400]=98689146716160000ll;
A[30420]=1782660928688640000ll;
A[30464]=44410116022272000ll;
A[30492]=1237958978256000000ll;
A[30576]=105594705216000000ll;
A[30600]=82598524968960000ll;
A[30618]=25670072838009600ll;
A[30720]=1732842634723200ll;
A[30780]=171804931935436800ll;
A[30800]=51741405555840000ll;
A[30870]=608472121257000000ll;
A[30888]=150535811755929600ll;
A[30912]=568449485085081600ll;
A[30976]=56206553090688000ll;
A[31050]=3616945935482880000ll;
A[31104]=2347722279302400ll;
A[31185]=135105646515840000ll;
A[31200]=10794125422080000ll;
A[31360]=6288541819560000ll;
A[31500]=51382090239480000ll;
A[31590]=45635685045350400ll;
A[31680]=3130296372403200ll;
A[31752]=8682524636385600ll;
A[31824]=1970650626623078400ll;
A[31920]=270322445352960000ll;
A[32000]=5415133233510000ll;
A[32032]=1221881588928000000ll;
A[32076]=29156132112307200ll;
A[32130]=508633022177280000ll;
A[32256]=2021649740510400ll;
A[32319]=1383481820322201600ll;
A[32340]=748888764624000000ll;
A[32400]=6994255957088400ll;
A[32448]=404687182252953600ll;
A[32500]=1610942942568960000ll;
A[32640]=28619852547686400ll;
A[32670]=643738668693120000ll;
A[32760]=46461670295040000ll;
A[32768]=2888071057872000ll;
A[32805]=54192375991353600ll;
A[32832]=82898883241574400ll;
A[32928]=37948097187000000ll;
A[33000]=63239495679360000ll;
A[33048]=109764262069862400ll;
A[33075]=413761042454760000ll;
A[33120]=442127377288396800ll;
A[33264]=10686184167859200ll;
A[33280]=8943703921152000ll;
A[33320]=4357170994176000000ll;
A[33440]=3128016867655680000ll;
A[33516]=3912561709056000000ll;
A[33600]=4891088081880000ll;
A[33660]=3169174984335360000ll;
A[33696]=14248245557145600ll;
A[33750]=218373883517790000ll;
A[33792]=4620913692595200ll;
A[34000]=367938883952640000ll;
A[34020]=16400324313172800ll;
A[34048]=177640464089088000ll;
A[34200]=330394099875840000ll;
A[34272]=62174162431180800ll;
A[34320]=342126844899840000ll;
A[34398]=794739097152000000ll;
A[34425]=960751264112640000ll;
A[34496]=86738507856000000ll;
A[34560]=3032474610765600ll;
A[34650]=389422157604480000ll;
A[34749]=1750969178845286400ll;
A[34776]=1903070015284838400ll;
A[34816]=47699754246144000ll;
A[34848]=78689174326963200ll;
A[34944]=16098667058073600ll;
A[34992]=11576699515180800ll;
A[35000]=478248686075160000ll;
A[35100]=67111301537280000ll;
A[35200]=11179629901440000ll;
A[35280]=16697162762280000ll;
A[35328]=610556854350643200ll;
A[35640]=15435599353574400ll;
A[35700]=1917155237437440000ll;
A[35721]=121932845980545600ll;
A[35840]=4332106586808000ll;
A[35904]=719443879560806400ll;
A[35910]=2034532088709120000ll;
A[36000]=13450492225170000ll;
A[36288]=6456236268081600ll;
A[36300]=2426399597381760000ll;
A[36400]=206965622223360000ll;
A[36450]=71305757883360000ll;
A[36480]=114479410190745600ll;
A[36504]=1354822305803366400ll;
A[36608]=224826212362752000ll;
A[36720]=75990642971443200ll;
A[36750]=2945005066883880000ll;
A[36800]=1579026347458560000ll;
A[36855]=540422586063360000ll;
A[36864]=4043299481020800ll;
A[36936]=439057048279449600ll;
A[36960]=24286782199680000ll;
A[37044]=235938169467000000ll;
A[37125]=735575186586240000ll;
A[37179]=1541472028198502400ll;
A[37260]=2748878910966988800ll;
A[37422]=102680291352038400ll;
A[37440]=12521185489612800ll;
A[37500]=1554308229744270000ll;
A[37632]=7797791856254400ll;
A[37800]=24118123989960000ll;
A[37908]=116624528449228800ll;
A[38000]=1471755535810560000ll;
A[38016]=9390889117209600ll;
A[38080]=222050580111360000ll;
A[38220]=2995555058496000000ll;
A[38250]=2769224231854080000ll;
A[38304]=248696649724723200ll;
A[38400]=6931370538892800ll;
A[38416]=3961451362869000000ll;
A[38475]=3843005056450560000ll;
A[38500]=3624621620780160000ll;
A[38556]=386561096854732800ll;
A[38610]=2574954674772480000ll;
A[38640]=4325159125647360000ll;
A[38720]=281032765453440000ll;
A[38808]=290385439344000000ll;
A[38880]=8608315024108800ll;
A[38912]=190799016984576000ll;
A[39000]=252957982717440000ll;
A[39168]=66779655944601600ll;
A[39200]=74378270486520000ll;
A[39204]=489241388206771200ll;
A[39312]=42744736671436800ll;
A[39366]=138491627533459200ll;
A[39424]=20123333822592000ll;
A[39600]=29683844910720000ll;
A[39690]=160437955237560000ll;
A[39744]=1326382131865190400ll;
A[39936]=18483654770380800ll;
A[39984]=1689515283456000000ll;
A[40000]=59915829003030000ll;
A[40095]=216769503965414400ll;
A[40128]=2877775518243225600ll;
A[40320]=6064949221531200ll;
A[40392]=2408572988094873600ll;
A[40500]=102502026957330000ll;
A[40560]=3079141604098560000ll;
A[40656]=2138292780624000000ll;
A[40768]=346954031424000000ll;
A[40800]=172706006753280000ll;
A[40824]=34730098545542400ll;
A[40950]=1557688630417920000ll;
A[40960]=8664213173616000ll;
A[41040]=303962571885772800ll;
A[41160]=889305407991000000ll;
A[41184]=314756697307852800ll;
A[41216]=2842247425425408000ll;
A[41310]=730170960725606400ll;
A[41472]=8086598962041600ll;
A[41580]=151000428458880000ll;
A[41600]=44718519605760000ll;
A[42000]=90906775039080000ll;
A[42120]=61742397414297600ll;
A[42240]=13862741077785600ll;
A[42336]=19368708804244800ll;
A[42525]=338702349945960000ll;
A[42560]=888202320445440000ll;
A[42768]=46306798060723200ll;
A[42840]=743386724720640000ll;
A[43008]=10108248702552000ll;
A[43092]=1546244387418931200ll;
A[43120]=1293535138896000000ll;
A[43200]=16678610359210800ll;
A[43264]=2023435911264768000ll;
A[43520]=143099262738432000ll;
A[43560]=940848823474560000ll;
A[43659]=3377641162896000000ll;
A[43680]=97147128798720000ll;
A[43740]=65601297252691200ll;
A[43776]=267118623778406400ll;
A[43875]=2942300746344960000ll;
A[43904]=157213545489000000ll;
A[44000]=132228036420480000ll;
A[44064]=227971928914329600ll;
A[44100]=462438812155320000ll;
A[44160]=1831670563051929600ll;
A[44226]=410721165408153600ll;
A[44352]=28172667351628800ll;
A[44550]=285223031533440000ll;
A[44800]=21660532934040000ll;
A[44928]=37563556468838400ll;
A[45000]=295447018877010000ll;
A[45056]=23104568462976000ll;
A[45360]=27977023828353600ll;
A[45600]=690824027013120000ll;
A[45696]=257578672929177600ll;
A[45760]=1124131061813760000ll;
A[45864]=1161541757376000000ll;
A[45900]=1073780824596480000ll;
A[45927]=487731383922182400ll;
A[46080]=12129898443062400ll;
A[46170]=2920683842902425600ll;
A[46200]=569155461114240000ll;
A[46332]=1956965552827084800ll;
A[46368]=3979146395595571200ll;
A[46464]=325998007925990400ll;
A[46592]=80493335290368000ll;
A[46656]=25824945072326400ll;
A[46800]=118735379642880000ll;
A[47040]=44019792736920000ll;
A[47104]=3052784271753216000ll;
A[47250]=873495534071160000ll;
A[47385]=867078015861657600ll;
A[47520]=34433260096435200ll;
A[47600]=3311449955573760000ll;
A[47628]=147602918818555200ll;
        rep(i, MAXN - 1) {
            if (i - div_num[i] < MAXM && Ans1[i - div_num[i]] == 0) Ans1[i - div_num[i]] = i;
        }
        int kase; scanf("%d", &kase); rep(_, kase) {
           printf("Case %d: ", _);
            int k, type; scanf("%d%d", &type, &k);
            if (type == 1) {
                if (Ans1[k] != 0) printf("%d\n", Ans1[k]); else puts("Illegal");
            } else {
                if (k == 1) puts("1"); else {
			  if (k >= 10000) {
				  if (A[k]) cout <<A[k]<<endl; else cout <<"INF"<<endl;
				  continue;
			  }
                    PII Ans = Dfs(0, k);
                    if (Ans == mp(inf, 0)) cout <<"INF"<<endl; else cout <<Ans.first<<endl;
                }
            }
        }
    }
}

int main(void) {
    #ifdef FILEIO
        freopen(INPUT, "r", stdin);
        freopen(OUTPUT, "w", stdout);
    #endif
    Solve::solve();
    return 0;
}
