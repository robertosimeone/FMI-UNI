/*
Допълнително упражнение за семафори - 
Изпит Shell - 27.01.24 - > като на шела ще са двете теоритични
Изпит С - 03.02.24
Изпит Теория - 06.02.24
*/


//Task 62 2017-SE-03
//Провери xxd и от колко байтове са 16тични числа
//add libraries
//tma kudeto go pravihme file1fd, file2fd,patchfd
/*----------------------------------------------------------------------------------------------------------------------------------------*/
struct patch{
    uint16_t offset;
    uint8_t orig;
    uint8_t new;
}

int main(argc,char ** argv){

    if(argc != 4){
        errx(1,"Invalid number of arguments for %s",argv[0]);
    }
    int fd1 = open(argv[1],O_RDONLY);
    if(fd1 == -1){
        err(2,"Opening file %s failed",argv[1]);
        
    }
    int fd2 = open(argv[2],O_CREAT | O_WRONLY | O_TRUNC,S_IRUSR);
    if(fd2 == -1){
        err(3,"Opening file %s failed",argv[2]);
        
    }
    int bytes_read;
    uint8_t byte;//tuk moje i char c zashtoto  e 1 byte
    while((bytes_read = read(fd1,&byte,sizeof(byte))) > 0){
            int byte_written;
            if((byte_written = write(fd2,&byte,sizeof(byte)) == -1)){
                err(5,”Could not write to file)”
            }
    }
    if(bytes_read == -1){
        err(6,”Could not read from file)”;
    }
    //tva s kopiraneto e shift v i posle tam komandite si za kopirane i pastevane na mnojestvo redove
    // dosta polezno za c chastta
            struct stat s;
        fstat(patchfd,&s);
        // proveri i tva sizeof(struct patch)
        if(s.st_size%sizeof(struct patch)!=0){
            errx(10,"patch file size not mod 4");
        }
    fstat(file1fd,&s);
    int file1size = s.st_size;
            

    struct patch p;
    //read prosto pliosva neshtata v bufera, v nashiq sluchai p
    // samo goleminata ima znachenie, nqma znachenie tipa na bufera
    // tuk proveri dali lseek kude slaga faillviq descriptor

    while(read(patchfd,&p,sizeof(p))){
        if(p.offset > =file1size){
            errx(100,"patch offset out of range")
        }
        if(lseek(fd1,p.offset,SEEK_SET) == -1){
            err(7,”lseek failed)”
        };
        uint8_t x;
        read(file1fd,&x,sizeof(x));
        if(x == p.orig){
        lseek(fd1,p.offset,SEEK_SET)
        write(file2fd,&p.new,sizeof(p.new))
        }

    }
    close(fd1);
    close(fd2);
    close(patchfd)

}

//write mislq che zapisvashe baitovete samo, kak zapivame neshta direktno na stdout naprimer?
unt8_t  - > kato zapishem edin bait tuk towa e prosto reprezzentaciqta

// binary file??
/*----------------------------------------------------------------------------------------------------------------------------------------*/
// zad65 2018-SE-02
// purvo trqbva da vidim dali chislata se pobirat v ramta
(4194304 * 4)/(1024*1024) = 16 - > nqma da se poberat

vij kak bachka fstat s fd - > ako premestq fd napred shte se pormenili razmera kak bachka

moje direktno da pravim zadachata vse edno e poveche ot 8mb


uint32_t * buffer = (uint32_t*)malloc(s.st_size)//aloira v heapa
v c ne ni se pozvolqva da suzdavame  ot promenlivi i zatova se polzwa tova gore
stacka e kraen resurs i moje da imame overflow,a a heapa raste kolkoto e nujni
moje da se prochete masiva na vednuj ako sme v dobriq sluchai

qsort funckiq


trudna chast// 16mn sa nujni imame 9
znachi v ramta moje da vzemem gd polvoitnata toest 8 mb
na dve chasti
free(buffer) sled malloc


nqma true vuv c, zatova se polzwa while(1)
merge sort
//full zadachata e wuw cpart w astero

                                                                        
                                                                        
                                                                        
                                                            ///////Next part theory/////
/*----------------------------------------------------------------------------------------------------------------------------------------*/
1.Само процес може да създаде друг процес(освен init - той е първия процес, който се стартира)
2.fork() е системното извикване,чрез което се създават процеси
3.При извикване на форк се създава "идентично" копие на извикващия процес

Какво реално става?
процес на програмата f1
Извикването на форк - > създава се втори ф1 процес, който е почти идентичен с първия(запазва се мястото от където може да чете, пише и тн,тоест контекста на ф1 се копира)
Това е единствения начин за създаване на процес, няма друг


4.exec - > заменя извикващия процес(този който вика exec фунцкията) exec(pogram_path) - > ф2 се превръща във процес който изпълнява примерно лс фунцкията

Като напишем ls просто в терминала, това което се случва е че първоначално имаме bash програмата, тя се форка до 2 свои варианта и единия от тях(детето) прави exec("ls")
и той се превръща в ls

execl(pathame,..arguments..,NULL);
Тоест извикването на лс е - > execl(/usr/bin/ls,,"ls",NULL) - > twa "ls" e prosto zashtoto towa e purviq argument на програмата.Ние можем да си изберем какъвто си искаме
 , но по конвеция е просто името на програмата
 execl i exelp shte ni trqbwav,един път е имало и вариантите с в накрая но малко вероятно са

 execlp("/bin/sleep","sleep","60")

 pid_t е просто alias за int,тоест ние просто може да напишем и int,няма да е проблем но това си е конвенция
 fork() return value
 - И двата процеса се изпълняват от същия ред код, демек там където имам форк (на реда) - > родителя след това си продължава, но детето също вижда форка и детето
 продължава нататък все едно текущо се е събудил(тоест детето почва на същоия ред на форка и затова има друга стоиност)
 ако имаме реда код 
 pid_t pid = fork()
 Родителя си продължава, а детето също продължава следи изпълнението на форка и променливата на детето също се пълни с return  стойност на fork()
 return vаlue при родителя ще бъде pid-a на детето
 return value на дете - > 0


 писане за буфера няма значение, тоест ядрото си се грижи за това, няма нужда от мутекс

int status
 wait(&status) - > чака някое от децата да завърши(завършването има различни неща, тоест може да бъде прератен и тн) и статуса се записва в status


 identation се освождава от 2 процеса






