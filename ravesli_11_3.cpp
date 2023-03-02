// ravesli_11_3.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>

using namespace std;

// Генерируем рандомное число между min и max
int getRandomNumber(int min, int max)
{
	static const double fraction = 1.0 / (static_cast<double>(RAND_MAX) + 1.0);
	// Равномерно распределяем генерацию значения из диапазона
	return static_cast<int>(rand() * fraction * (max - min + 1) + min);
}

class Creature
{
public:
	Creature(string n = "", char s = '\0', int h = 0, int sp = 0, int g = 0):
		name(n), symb(s), health(h), spoil(sp), gold(g)
	{}
	~Creature()
	{}
	const string& getName() const
	{
		return name;
	}
	char getSymb() const
	{
		return symb;
	}
	int getHealth() const
	{
		return health;
	}
	int getSpoil() const
	{
		return spoil;
	}
	int getGold() const
	{
		return gold;
	}
	void reduceHealth(int n)
	{
		health -= n;
	}
	bool isDead()
	{
		if (health > 0)
			return false;
		return true;
	}
	void addGold(int n)
	{
		gold += n;
	}

protected:
	string name;
	char symb;
	int health;
	int spoil;
	int gold;
};

class Player: public Creature
{
public:
	Player(string n) :
		Creature(n, '@', 10, 1, 0), level(1)
	{
	}
	~Player()
	{}
	void levelUp()
	{
		level++;
		spoil++;
	}
	int getLevel() const
	{
		return level;
	}
	bool hasWon() const
	{
		if (level >= 20)
			return true;
		return false;
	}

private:
	int level;

};

class Monster: public Creature
{
	
public:
	enum Type
	{
		DRAGON,
		ORC,
		SLIME,
		MAX_TYPES
	};

	Monster(Type type)
		: Creature(monsterData[type].name, monsterData[type].symbol, monsterData[type].health, monsterData[type].damage, monsterData[type].gold)
	{
	}
	~Monster()
	{}
	struct MonsterData
	{
		const char* name;
		char symbol;
		int health;
		int damage;
		int gold;
	};
	static MonsterData monsterData[MAX_TYPES];
	static Monster getRandomMonster()
	{
		int num = getRandomNumber(0, MAX_TYPES - 1);
		return Monster(static_cast<Type>(num));
	}

private:

};

Monster::MonsterData Monster::monsterData[Monster::MAX_TYPES]
{
	{ "dragon", 'D', 20, 4, 100 },
	{ "orc", 'o', 4, 2, 25 },
	{ "slime", 's', 1, 1, 10 }
};

void mainFunc()
{
	string name;
	char res;
	cout << "Enter name" << endl;
	cin >> name;
	Player p(name);
	while (true)
	{
		Monster m = Monster::getRandomMonster();
		std::cout << "A " << m.getName() << " (" << m.getSymb() << ") was created.\n" << "health: "
			<< m.getHealth() << " Spoil: " << m.getSpoil() << endl;
		cout << "Run (r) or fight(any)?" << endl;
		cin >> res;
		if (res == 'r')
		{
			if (getRandomNumber(0, 100) > 50)
			{
				cout << "run" << endl;
				continue;
			}
			else
			{
				cout << "not run" << endl;
				p.reduceHealth(m.getSpoil());
				cout << p.getHealth() << endl;
			}
		}
		else
		{
			m.reduceHealth(p.getSpoil());
			if (m.isDead())
			{
				p.addGold(m.getGold());
				p.levelUp();
				p.reduceHealth(1);
				cout << "monster dead" << endl;
				cout << p.getHealth() << endl;
			}
			else
			{
				p.reduceHealth(m.getSpoil());
				cout << "monster not dead" << endl;
			}
		}
		if (p.isDead())
		{
			cout << "dead" << endl;
			break;
		}
		if (p.hasWon())
		{
			cout << "won" << endl;
			break;
		}
	}
	cout << p.getLevel() << "gold" << p.getGold() << endl;

}
int main()
{
	srand(static_cast<unsigned int>(time(0))); // устанавливаем значение системных часов в качестве стартового числа
	rand(); // сбрасываем первый результат
	mainFunc();
	

	return 0;
}
// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
