#include <iostream>
#include <string>
#include <fstream>
#include <cmath>

using namespace std;

class City {

public:
    int people = 100;
    int food = 2800;
    int size = 1000;
    int round=1;
    int landPrice;
    int landBuy;
    int LandSell;
    int foodEat;
    int foodPlant;
    float deadRatio=0;
    bool gameOver = 0;
    bool save=0;
    bool load=0;
    ofstream fout;
    ifstream fin;


    void gameStart() {

        cout << "Меню\n 1 - Загрузить сохранение\n 0 - Начать новую историю \n";

        load=input(load);
       
        if (load) {
            fin.open("saveData.txt");

            if (fin.is_open())
            {
                fin >> round >> people >> size >> food;
                cout << "Загрузка завершена \n сейчас идет " << round << " год Вашего правления \n";
            }
            else cout << "Ошибка сохранение\n\nНачало новой игры\n\n\n";
            
        }

        cout << " \t Население города  " << people << " человек \n";
        cout << " \t Город распологается на " << size << " акрах \n";
        cout << " \t в амбарах " << food << " бушелей пшеницы \n";

        landPrice = rand() % 10 + 17;
        cout << " \t 1 акр земли стоит " << landPrice << " бушель \n";

        orders();
    }

    void newDay() {


        size += landBuy;
        food -= landPrice * landBuy;
        food -= foodEat;
        


        int foodGrowth = (rand() % 6 + 1);

        food += foodPlant * foodGrowth;
        float RatDamage = static_cast <float>(rand() % 8) / 100 * food;
        food -= ceil(RatDamage);
        
        int deadPeople = people - foodEat / 20;
             if (deadPeople <= 0) deadPeople = 0;
           
      

        int newPeople = deadPeople / 2 + (5 - foodGrowth) * food / 600 + 1;
             if (newPeople <= 0) newPeople = 0;
             if (newPeople >= 50) newPeople = 50;
         
        people += newPeople;

        deadRatio += static_cast<float>(deadPeople) / people;

        people -= deadPeople;

        bool plague =false;
        int plagueRand = (rand() % 100);
        if (plagueRand < 15) plague = true; else plague = false;

        if (plague) people /= 2;
    
  
        landPrice = rand() % 10 + 17;

        
            cout << " Повелитель, извольте поведать Вам \n \t в году " << round << " Вашего высочайшего правления\n";
            if (deadPeople != 0) cout << "\t " << deadPeople << " человек умерли с голоду \n";
            if (newPeople != 0)  cout << "\t " << newPeople << " человек прибыли в Ваш великий город \n";
            if (plague)  cout << " \t Чума уничтожила половину населения \n";
            cout << " \t Население города сейчас составляет " << people << " человек \n";
            cout << " \t Мы собрали " << foodPlant * foodGrowth << " бушелей пшеницы, по " << foodGrowth << " бушелей с акра \n";
            cout << " \t Крысы истребили " << ceil(RatDamage) << " бушелей пшеницы, оставив " << food << " бушелей в амбарах \n";
            cout << " \t Город сейчас занимает " << size << " акров \n";
            cout << " \t 1 акр земли стоит сейчас " << landPrice << " бушелей \n";
        

        
        
            if ((deadPeople * 100 > people * 45)||(people == 0)) GameOver();
      
            round++;

    }

    int input(int value) {
        for (;;) {
            if (cin >> value) {
                break;
            }
            else {
                cout << "\nЯ должно быть неправильно услышал, повторите, пожалуйтса:\n\n ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        }
        return value;
    
    }

    bool input(bool value) {
        for (;;) {
            if (cin >> value) {
                break;
            }
            else {
                cout << "\nЯ должно быть неправильно услышал, повторите, пожалуйтса:\n\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        
        }
        return value;
    }


    void orders() {        

        cout << " Что пожелаешь, повелитель ?\n";
        cout << " \t Сколько акров земли повелеваете приобрести?\n ";   
        landBuy=input(landBuy);
        cout << " \t Сколько акров земли повелеваете продать?\n";
        LandSell = input(LandSell);
        cout << " \t Сколько бушелей пшеницы повелеваете отдать на съедение? \n";
        foodEat=input(foodEat);
            

        cout << " \t Сколько акров земли повелеваете засеять? \n";
        foodPlant=input(foodPlant);
              

        while (((landBuy * landPrice + foodEat + foodPlant / 2) > food) || (foodPlant > people * 10) || (size + landBuy - LandSell < 0) || (foodPlant > size + landBuy))
        {
            cout << " У нас осталось лишь " << people << " человек, " << food << " бушелей пшеницы и " << size << " акров земли! \n";

            orders();
        }
   
        
    
    }

    void saveGame() {
                
        cout << "желаете сохранить игру и выйти?\n(1 - да, 0 - нет) \n" ;

        save=input(save);

        if (save)
        {         
            fout.open("saveData.txt");

           

            if (fout.is_open()) {

                fout << round << "\n" << people <<"\n"<< size << "\n" << food;
                gameOver = true;
                cout << "игра сохранена";

            }else{
                cout << "ошибка сохранения";
            }

            fout.close();

        }

    }
  
    void GameOver()
    {
        cout << " \t Игра окончена, слишком много жителей погибло ";
        gameOver = true;
        
    }
};


int main()
{
    int gameLenght = 11;
    setlocale(LC_ALL, "Rus");

    srand(time(NULL));
  
    City city;
  
    city.gameStart();

    for (city.round; city.round <= gameLenght; )
    {
        city.newDay();
        if ((city.gameOver)||(city.round == gameLenght)) break;
        city.saveGame();
        if (city.save) break;
        city.orders();
        
    }  
   
   if (!city.gameOver) {
       cout << "\n среднее количество умерших = " << city.deadRatio / city.round << "\n площадь земли на одного человека = " << ceil(city.size / city.people);
       if ((city.deadRatio / city.round < 0.03) && (ceil(city.size / city.people) > 10))
           cout << " \t Игра окончена, оценка - 5"; else {
           if ((city.deadRatio / city.round < 0.10) && (ceil(city.size / city.people) > 9))
               cout << " \t Игра окончена, оценка - 4"; else {
               if ((city.deadRatio / city.round < 0.33) && (ceil(city.size / city.people) > 7))
                   cout << " \t Игра окончена, оценка - 3"; else {
                   cout << " \t Игра окончена, оценка - 2";
               }
           }
       }
   } 


   system("pause");
}
