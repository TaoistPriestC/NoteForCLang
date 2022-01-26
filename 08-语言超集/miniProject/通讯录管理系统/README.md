### 结构体设计

　　通讯录的人员包括姓名、电话、家庭地址、性别、年龄，最初人员的前三条属性都采用了`string`实现，但是这种实现不利于数据持久化，因为`string`对象本质就是一个动态的`char`数组，其存储的是一个地址，而当结构体成员变量存储地址的时候，`fread`和`fwrite`非常容易出错，试想上一次存入文件的地址，下一次读出来的时候已然失效不再适用了。`string`对象如何数据持久化处理，目前尚未习得，改用`char`数组能使整体代码风格更一致。

```c++
typedef struct _Person{
    std::string name;
    std::string tel;
    std::string addr;
    unsigned char sex;
    unsigned char age;
} Person;
```

　　改用`char`数组可能引起的担忧便是有可能会有空间浪费，但是绝大部分的管理都有这种长度限制，至于数据库的`varchar`类型，是在实际存储的时候多用一个字节用来存放长度，通常读取长度来获取接下来连续字节的内存。

```c++
typedef struct _Person{
    char name[30];
    char tel[30];
    char addr[30];
    unsigned char sex;
    unsigned char age;
} Person;
```



### 数据持久化

　　这个项目比较初级，没有用到数据库，仅仅是采用简单读写文件的方式实现持久化处理，退出系统的时候，系统会检测通讯录是否发生改变，如果发生变更则将全新的通讯录覆盖写入`database`文件，这种做法的缺点是尽管只有少量修改也要全部覆盖，而且明文存储，保密性不好。

```c
void initContact(){
    File fp = openFile("database", "r+");
    fscanf(fp, "%ld\n", &adbs.size);
    for (int i = 0; i < adbs.size; i++){
        fscanf(fp, "%s %s %s %hhd %hhd\n",
            &adbs.contactList[i].name[0],
            &adbs.contactList[i].tel[0],
            &adbs.contactList[i].addr[0],
            &adbs.contactList[i].sex,
            &adbs.contactList[i].age);
    }
    adbs.isChange = 0;
    closeFile(fp);
}

void exitContact(){
    printf(WELCOME_NEXT_TIME);
    if(adbs.isChange){
        File fp = openFile("database", "w+");
        fprintf(fp, "%ld\n", adbs.size);
        for (int i = 0; i < adbs.size; i++){
            fprintf(fp, "%s %s %s %hhd %hhd\n",
                adbs.contactList[i].name,
                adbs.contactList[i].tel,
                adbs.contactList[i].addr,
                adbs.contactList[i].sex,
                adbs.contactList[i].age);
        }
        closeFile(fp);
    }
    cls();
    exit(EXIT_SUCCESS);
}
```

