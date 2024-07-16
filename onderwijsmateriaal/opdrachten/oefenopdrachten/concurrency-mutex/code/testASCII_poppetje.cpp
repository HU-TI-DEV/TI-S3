//#include "stdafx.h"

#include <iostream>
#include <thread>
#include <mutex> 
#include <windows.h> // for sleep.
using namespace std;

enum type_wenkbrauwen { w_lief, w_neutraal, w_boos };
enum type_ogen { o_open, o_dicht };
enum type_mond { m_open, m_dicht, m_boos };
type_wenkbrauwen wenkbrauwen = w_lief;
type_ogen		 ogen = o_open;
type_mond		 mond = m_dicht;
mutex mtx_wenkbrauwen;
mutex mtx_ogen;
mutex mtx_mond;

void wenkbrauwenController()
{
	while (true)
	{
		mtx_wenkbrauwen.lock();		// want mond gaan we hier schrijven.
		switch (wenkbrauwen) {
		case w_lief:wenkbrauwen = w_neutraal;	break;
		case w_neutraal:wenkbrauwen = w_boos;		break;
		default:wenkbrauwen = w_lief;		break;
		}
		mtx_wenkbrauwen.unlock();	// Dan kan ook de mondManager wenkbrauwen lezen.
		Sleep(4000);		// verander eens per 4 sec.
	}
}

void mondController()
{
	while (true)
	{
		mtx_wenkbrauwen.lock();	// want uit wenkbrauwen gaan we hier lezen.
		mtx_mond.lock();		// want mond gaan we hier schrijven.
		if (wenkbrauwen == w_boos) {
			mond = m_boos;
		}
		else // mond gaat open en dicht
		{
			switch (mond) {
			case m_open:mond = m_dicht;	break;
			default:mond = m_open;		break;
			}
		}
		mtx_wenkbrauwen.unlock();
		mtx_mond.unlock();
		Sleep(500);			// update elke halve seconde
	}
}

void ogenController()
{
	while (true)
	{
		mtx_ogen.lock();		// want ogen gaan we hier schrijven.
		switch (ogen) {
		case o_open:ogen = o_dicht;	break;
		default:ogen = o_open;		break;
		}
		mtx_ogen.unlock();	// Dan kan ook de mondManager wenkbrauwen lezen.
		Sleep(5500);			// update elke ruim 5 seconden
	}
}

void afbeeldTaak()
{
	while (true)
	{
		cout << endl << endl;

		mtx_wenkbrauwen.lock();	// want uit wenkbrauwen gaan we hier lezen.
		mtx_ogen.lock();		// want uit mond gaan we hier lezen.
		mtx_mond.lock();		// want uit mond gaan we hier lezen.

		switch (wenkbrauwen) {
		case w_boos:cout << "  \\   /" << endl;break;
		case w_lief:cout << "  /   \\" << endl;break;
		default:cout << "  w   w" << endl; break;
		}
		switch (ogen) {
		case o_open:cout << "  O   O" << endl;break;
		default:cout << "  _   _" << endl; break;
		}
		cout << "    U" << endl; // neus
		switch (mond) {
		case m_open:cout << "    O" << endl;break;
		case m_dicht:cout << "   ---";break;
		default:cout << "  /```\\" << endl; break;
		}
		cout << endl << endl << endl;	// wat ruimte ertussen

		mtx_wenkbrauwen.unlock();	// want uit wenkbrauwen gaan we hier lezen.
		mtx_ogen.unlock();		// want uit mond gaan we hier lezen.
		mtx_mond.unlock();		// want uit mond gaan we hier lezen.

		Sleep(250);				// limiteer tot 4 gezichtjes per seconde.
								// dan zal de serial bus en de console het wel
								// bij kunnen houden.
	}
}

int main(int argc, char **argv) {
	thread t_wenkbrauwen(wenkbrauwenController);
	thread t_ogen(ogenController);
	thread t_mond(mondController);
	thread t_afbeelder(afbeeldTaak);
	t_wenkbrauwen.join();
	t_ogen.join();
	t_mond.join();
	t_afbeelder.join();
	return 0;
}

// abort has been called = serial buffer overflow

