този петък 12.01.24 - > отучване по ос от 10:15-14:00
зала 304
2016-SE-02-Zad79
//чете от стандартния си вход
#include <assert.h> -> ne sum siguren kakvo shte e tva
//strcat - > vij
cstring
int main(void){
    if(write(1,">",2)==-1){
        err(1,"Could not write to stdout");
    }
    //ние си преценяваме колко да е голям буфера
    //ама принципно си го казват в условието колко гд ще е голямо
    char bugger[256] = '/bin/'; - > towa vse edno e izchistvane na bufera- > te si chetat do terminirashta nula
    int i = 5 ;
    while(1){
        //ако напишем date интервал
//        read(0,&buffer,256);
        char symbol;
        while(1){
            //tuk izpolzwame samo edin byte защото ако реаднем по малко то се блокира
            // по този начин се чете от stdin
            if(read(0,&symbol,sizeof(symbol)) == -1){
                err(2,"could not read")
            }
            if(symbol == ''n)
                break;
            else{
                buffer[i] = symbol;
                i++;
                asser(a<255);//mqsto za terminirashta nula
                }

        }
        if(strcmp(buffer,"/bin/exit") == 0){
            break;
        }
        buffer[i] = '\0';
        i = 5 ;
        const pid_t pid = fork();
        if(pid == -1){
            err(4,"Could not fork");
        }
        if(pid == 0){
            if(execl(buffer,buffer,NULL)==-1){
                err(3,"Could not exec");
            }
        }
        }
    //тук ако не чакаме то родителя сис е блокира зщаото реад иска да чете но няма нищо на буфера и като има нещо вече той си се отблокира
    //също така горе на онова използваме 1 байт защото се блокриа реада,защото реада не спира да чете до края на нов ред- > само до край на файл или нещо си там
    //тоест той се опитва да прочете 50 символа например обаче има само 5, и той чака 45 още

    int status;
    wait(&status);
    if(!WIFEEXITED(status)){
        errx(4,"err");
    }


    return 0;
}
81 - > 2017-IN-02
тва стринг на ехото е просто поредица от байтове
//защо е статик? ако премахнем статик makefile ни дава warning,
//ако има дефиниция но няма декларация се оплаква
// ако кажем че фунцкията е статична тва значи че функцията ще бъде видима само във текущия файл и с не се оплаква
//имаме дефиниция но нямаме декларация реално за тва долу
шано начин за правене на проверки
nawsqkyde kudeto izwikame check_err se izwikwa wtorotot parche kod
синтетично заместване - > тоест inline;
#define CHECK_ERR(result_code,err_code,msg) if(result == -1) err(err_code,msg);
static void func(char* buf,int fd){
    char symbol;
    int counter = 0;
    int bytes_read;
    //while  във с всичко е вярно, освен 0та
    while((bytes_read=read(fd,&symbol,sizeof(symbol)))>0){

        if(symbol != '\n' and symbol !=' '){
        buf[counter] = symbol;
        counter++;
        }
        else
            break;
        if(i == 4){
            break;
        }
    }
    if(bytes_read == -1){
        err(1,"Read failed");
    }
    buf[counter] = '\0';
}
int main(int){

    char p1[5];
    char p2[5];
    //
    това е константет пойнтър - > тоест не може да се сменя къде сочи
     char * const char
    това е пойнтър към констрантет чар

   const char * cmd = "echo" - > константен масив,стринг просто си;така като го дадем си е с големина 5 - > 4 за echo и 1 за терминираща нула
    cmd = argv[1];
    while(){
        func(p1,0);
        if(strlen(p1) == 0){
            break;
        }
        func(p2,0);
        if(strlen(2) == 0){
            const pid_t pid = fork();
            CHECK_ERR(pid,3,"Could not fork");
            if(pid == 0){
                execlp(cmd,cmd,p1,NULL);
            }
        }
        else{
               const pid_t pid = fork();
               CHECK_ERR(pid,3,"Could not fork");
        if(pid == 0){

                execlp(cmd,cmd,p1,p2,NULL);
            }
        }
    }
    //този уейт е във while
    wait(NULL);


    return 0;
}

------------------------------------------------------------------------Тръбене------------------------------------------------------------------------
man pipe(7);
man pipe(2)
Да ги прочета
Приема във входа си някакви байтове, и тези байтове могат да излизат от другата страна
Тя е FIFO
Комуникацията чрез тръба става само между родител-дете процеси(може и примерно родител и пра дете)
Тази тръба се наричана неименувана()
Тръбата реално е като файл,той няма име, но има файлове дескриптор но няма име върху файловата система
Именуваните тръби вече си имат имена върху файловата система
Когато единия пише, другите не могат;

int fds[2];
pipe(fds);
fd[0] = през този може да се read
fd[1] = през този може да се write

        при форк файловите дескриптора са едни и същи и затова това с pipe  бачка
        даже и оффсета е същия на файловия дескриптор
        тръбата гарантира че записването от началото до края няма нищо да се прекъсне(като цяло това е свойство на write, тоест дори и към файл да пишем си е така)




        child процес и като цяло програма може да се терминира с exit(exit_code) - >

        ако някоя функция е с главни букви във С, то това е макро

        const int savederrorcode = errno
                close(fd);
        errno = savederrorcode
                err(...)



Когато правим тръба, това което трябва да направим е да затворим частта на pipe, koqto ne izpolzwame,защото се опита процес да чете от тръба и има друг процес който вижда тази тръб
но не е затворил частта на тръбата за писане този read никога няма да приключи.
read -  >blokira pri
края за писане в тръбата(write) в pf[1]
pf[0]- > read
        когато спре пак си затваря неговата част
        момента в който процес си е затворил и двата краища на тръбата , осто казва този процес вече не го интересува тръбата


Операционна система използва най ниския файлов дексрирпро който не е използвала досега
0 1 2 заети ->  3 4 например
В тази примерната задача wait-ваме и принтването става малко гадно
rado@astero:~/C/pipes/task2$
./a.out asdf
3
A
asdfrado@astero:~/C/pipes/task2$
./a.out asdf
3 4
asdfrado@astero:~/C/pipes/task2$
/a.out asdf
3 4
asdfrado@astero:~/C/pipes/task2$
./a.out asdf
3 4
asdfrado@astero:~/C/pipes/task2$
./a.out asdf
3 4
asdfrado@astero:~/C/pipes/task2$./a.out asdf
3 4
asdrado@astero:~/C/pipes/task2$ f./aout. asdf
eto towa stawa
Тоест главния приклщчвам изписва се промпта и после и детето приклщчва

Ako se opitame da pishem v truba, i tam nqma koi da chete, to nqma da blokirame
Write ne blokira no read blokira

Pipe blokira samo ako pone edin ne si e zatworil write chastta
Ako primerno deteto chete, a parent si e zatworil write i read - > osto kazva che nqma kakvo da se chete poveche i deteto ne blokira


---------------------------------------------------------------------------------dup------------------------------------------------------------------------------------------
0 - > in
1 - > out
2 - > err


Примерно програма п1 чете нешо от 0 ,прави нещо с данните и после пише на 1
Можем да направим следния трик
Иксаме да извика п1 обаче искаме не да чете от стандартния вход а от някакъв файл
Имаме родителския процес , п1 е дете
В родителя ще се отвори пешо.тхт -  >   fd = open(pesho.txt)
        родителя форква
        if(pid ==0){
            тук сме в детето
            zatwarqme standartniq whod
            close(0);
            извикваме dup(fd)
            //реално след дуп ще имаме 2 фйалови дексриптора
            execlp() но еxec работи със стандартния си вход
            //дуп дуплицира файловия дексриптор на първото място отдолу нагоре, тоест на 0 защото го затворихме преди малко
            със stdout е същото
        }





pipe(fds)
pid1 = fork()
        if(pid1 == 0){
            close(1);
            close(fds[0]);
            dup(fds[1]);
            execlp(...)
        }


        pid2 = fork();
        if(pid 2 == 0){
            close(0);
            close(f[1])
            dup(fds[0])
            execlp(...)
        }


        Тръбата имам максимален капацитет - > ако един процес се опитва да пише към тръба и се опита да запише повече от еди си колко байта, ако пише повече от капацитета на тръбата то еще блокира?

        dup2 e kato dup1 samo che izpolzwa drug failov deksriptor

        toest close-a po gore moje da go zamenim dup2(fds[1],1);
        plusut е че се случва атомарна затваряне и копирането
        така че дуп2 е по-добре,защото може някоя друга нишка да направи нещо



    В горния пример когато използваме дуп и после екзек какво става с отворения досега край на пайпа???
    Отговор:
    exec не стартира нов процес, просто парчето от паметта в рамта,което съдържда 
    когато прикл екзекнатия процес си затваря вс файлови дескериптор и зартова не ни трябва да затваряме write stranata

    Операционна система създва процес-  той си има stdin,out,err
    Има втори процес ,който е примерно някакъв наследник - той също има stdout,in
    имаме тръба, който си има fd[0],fd[1]
    Когато екзекнем
