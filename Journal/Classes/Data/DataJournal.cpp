//
//  DataJournal.cpp
//  Journal-mobile
//
//  Created by liuwei on 2018/2/6.
//

#include "Journal.h"
#include "CommonUtils.h"
#include "DataJournal.h"
using namespace std;

CDataJournal::CDataJournal()
{
    //临时数据
    vector<string> title = {
        "About Bike-sharing",
        "The Misunderstanding In Culture",
        "Chinese English",
        "My Fear",
        "The Power of Example",
        "The Power of Insistence",
        "The Young Star",
        "The Happy Moment",
        "The Best Idols",
        "The Best Way to Learn",
        
    };
    vector<string> preview = {
        "Bike-sharing has been advocated by the government in recent years.",
        "Since I go to high school, I am so excited about English class, because we have a foreign teacher, whose name is Paul. Paul likes to share funny things about how foreigners think about China. The way he talks makes us laugh out loudly.",
        "China has the largest population in the world and English is the international language. There are a lot of funny things when Chinese people learn English. They will mix the words with their own language. Some very classic words have been created. Such as the sentence long time no see, it is the most classic words that were spoken by Chinese.",
        "I like watching horror movie. My friends admire me for this reason. But before, I was very afraid of horrible things, like ghost story, even in the dark would scare me.",
        "Chinese army has caught the world’s attention after they showed the world the new images. Many people feel so proud of Chinese new power. Recently, the picture of a little boy standing behind the soldiers was favored by a lot of people.",
        "People always say that if you want to be successful, then you need to never give up. I agree with it. The power of insistence is infinite. It can bring us to our destination. I have made up my mind to finish the task in the planned time. ",
        "As the development of media, many children become famous. As they get the fame at the early age, their life is influenced. They can’t live the normal life as other children have. For example, some schools refuse to receive famous kids, because the school is afraid of out of control, then many students will be affected and can’t focus their attention on study.",
        "Last week, my parents told me the good news that my family would go camping with my uncle’s family. I felt so excited about it, because I could spend the whole night outside, which never happened before. When the day came, ",
        "Most young people have idols, and the popular stars are always treated in the first place in their hearts. In order to see their idols, some people will do a lot of crazy things, such as skip class or save money to buy a concert ticket. ",
        "I always feel it a burden to learn knowledge after I go to school. As a small girl, I just want food and hang out to play for fun. Study seems the most difficult thing for me. Later, I figure out that the reason why I refuse to study is because I lack of interest. ",
    };
    for (int i = 0; i < 10; ++i)
    {
        Journal_Info info;
        info.strTitle = title[i];
        info.strPreview = preview[i];
        info.strContent = preview[i];
        info.createTime = getTimeStamp() - rand() % 1000;
        info.vecMessage = vector<std::string>();
        info.lickCount = rand() % 255;
        info.isPublic = i < 8;
        m_vecJournals.push_back(info);
    }
    
    //根据创建时间排序
    
    std::sort(m_vecJournals.begin(), m_vecJournals.end(), [](const Journal_Info&lhs, const Journal_Info& rhs){
        return lhs.createTime < rhs.createTime;
    });
}

CDataJournal::~CDataJournal()
{
}


const std::vector<Journal_Info>& CDataJournal::getJournals()
{
    return m_vecJournals;
}
