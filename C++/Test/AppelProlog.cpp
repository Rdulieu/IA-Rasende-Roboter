#include <stdlio>

public void main(){

	PrologInterface m_PrologInterface;
	m_PrologInterface.init( “prgp.exe” );

	if (m_PrologInterface.start( "startThinking", 1 )) // Le prédicat startThinking ayant un argument va être testé
	{
		if (m_PrologInterface.call()) // teste le prédicat Prolog
		{
			cout << "Thinking initialized!" << endl;
		}
	else
	{
		cout << "Thinking NOT initialized!" << endl;
	}
		m_PrologInterface.finish(); // indique que le prédicat a fini d'être testé
	}
}
