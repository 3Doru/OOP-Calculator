    #include <iostream>
    #include <string>
    #include <cmath>
    #include <fstream>
    #include <map>

    using namespace std;

    class ValidareString
    {
        
    public:

        bool operator!() const
        {
            return expresie.empty();
        }

        bool operator==(const ValidareString& other) const {
            return this->expresie == other.expresie;
        }

        void setExpresie(const string& expr) {
            expresie = expr;
        }

        string getExpresie() const {
            return expresie;
        }

        void citeste_de_la_tastatura()
        {
            cout << "Introduceti un calcul: ";
            getline(cin, expresie);
        }

        bool valideaza_expresia()
        {
            for (int i = 0; i < expresie.size(); ++i)
            {
                char c = expresie[i];

                if (c < '0' || c > '9' || c == ',')
                {
                    return false;
                }

                if (!is_digit_or_symbol_or_space(c))
                {
                    return false;
                }
            }
            for (int i = 0; i < expresie.size(); ++i)
            {
                if ((expresie[i] == '+' && i < expresie.size() - 1 && expresie[i + 1] == '+') || (expresie[i] == '+' && i < expresie.size() - 1 && expresie[i + 1] == '-') || (expresie[i] == '+' && i < expresie.size() - 1 && expresie[i + 1] == '*') || (expresie[i] == '+' && i < expresie.size() - 1 && expresie[i + 1] == '/') || (expresie[i] == '/' && i < expresie.size() - 1 && expresie[i + 1] == '+') || (expresie[i] == '*' && i < expresie.size() - 1 && expresie[i + 1] == '+') || (expresie[i] == '-' && i < expresie.size() - 1 && expresie[i + 1] == '+') || (expresie[i] == '-' && i < expresie.size() - 1 && expresie[i + 1] == '-') || (expresie[i] == '-' && i < expresie.size() - 1 && expresie[i + 1] == '/') || (expresie[i] == '-' && i < expresie.size() - 1 && expresie[i + 1] == '*') || (expresie[i] == '*' && i < expresie.size() - 1 && expresie[i + 1] == '*') || (expresie[i] == '*' && i < expresie.size() - 1 && expresie[i + 1] == '/') || (expresie[i] == '*' && i < expresie.size() - 1 && expresie[i + 1] == '+') || (expresie[i] == '*' && i < expresie.size() - 1 && expresie[i + 1] == '-') || (expresie[i] == '/' && i < expresie.size() - 1 && expresie[i + 1] == '/') || (expresie[i] == '/' && i < expresie.size() - 1 && expresie[i + 1] == '*')) {
                    return false;
                }
            }

            for (int i = 0; i < expresie.size(); ++i)
            {
                if (expresie[i] == '/' && i < expresie.size() - 1 && expresie[i + 1] == '0')
                {
                    return false;
                }
            }

            for (int i = 0; i < expresie.size(); ++i)
            {
                if (expresie[i] == '(' && i < expresie.size() - 1 && expresie[expresie.size()] == '0')
                {
                    return false;
                }
            }

            for (int i = 0; i < expresie.size(); ++i)
            {
                if (expresie[i] == '.' && i < expresie.size() - 1 && expresie[i + 1] == '.')
                {
                    return false;
                }
            }

            int numarParantezeRotunde = 0;
            int numarParantezePatrate = 0;

            for (int i = 0; i < expresie.size(); ++i)
            {
                char c = expresie[i];

                if (c == '(')
                {
                    numarParantezeRotunde++;
                }
                else if (c == ')')
                {
                    numarParantezeRotunde--;
                    if (numarParantezeRotunde < 0) {
                        return false;
                    }
                }
                else if (c == '[')
                {
                    numarParantezePatrate++;
                }
                else if (c == ']')
                {
                    numarParantezePatrate--;
                    if (numarParantezePatrate < 0)
                    {
                        return false;
                    }
                }
            }


            if (numarParantezeRotunde != 0 || numarParantezePatrate != 0)
            {
                return false;
            }


            return true;
        }


        double getNumar1()
        {
            return stringToDouble(expresie);
        }

        double getNumar2()
        {
            size_t pozitiaOperatorului = 0;
            while (pozitiaOperatorului < expresie.size() &&
                expresie[pozitiaOperatorului] != '+' &&
                expresie[pozitiaOperatorului] != '-' &&
                expresie[pozitiaOperatorului] != '*' &&
                expresie[pozitiaOperatorului] != '/' &&
                expresie[pozitiaOperatorului] != '^' &&
                expresie[pozitiaOperatorului] != '#')
            {
                ++pozitiaOperatorului;
            }

            if (pozitiaOperatorului < expresie.size() - 1)
            {
                return stringToDouble(expresie.substr(pozitiaOperatorului + 1));
            }
            else
            {
                cout << "Expresie nevalida! Operatorul nu are numar2." << endl;
                return 0.0;
            }
        }


        char getOperator()
        {
            size_t pozitiaOperatorului = 0;
            while (pozitiaOperatorului < expresie.size() &&
                expresie[pozitiaOperatorului] != '+' &&
                expresie[pozitiaOperatorului] != '-' &&
                expresie[pozitiaOperatorului] != '*' &&
                expresie[pozitiaOperatorului] != '/' &&
                expresie[pozitiaOperatorului] != '^' &&
                expresie[pozitiaOperatorului] != '#')
            {
                ++pozitiaOperatorului;
            }

            return expresie[pozitiaOperatorului];
        }

    private:
        string expresie;

        double stringToDouble(const string& expresie)
        {
            double rezultat = 0.0;
            bool negativ = false;
            bool inParanteze = false;

            size_t index = 0;


            for (; index < expresie.size() && expresie[index] >= '0' && expresie[index] <= '9'; ++index)
            {
                rezultat = rezultat * 10 + (expresie[index] - '0');
            }

            if (index < expresie.size() && expresie[index] == '.')
            {
                double putere = 0.1;
                for (++index; index < expresie.size() && expresie[index] >= '0' && expresie[index] <= '9'; ++index)
                {
                    rezultat += (expresie[index] - '0') * putere;
                    putere *= 0.1;
                }
            }

            if (inParanteze)
            {
                size_t inchidereParanteza = expresie.find(')');
                if (inchidereParanteza != string::npos)
                {
                    return negativ ? -stringToDouble(expresie.substr(1, inchidereParanteza - 1))
                        : stringToDouble(expresie.substr(1, inchidereParanteza - 1));
                }
                else
                {
                    cout << "Expresie nevalida! Paranteza nu este inchisa corect." << endl;
                    return 0.0;
                }
            }

            return (negativ) ? -rezultat : rezultat;
        }

        bool is_space(char c)
        {
            return (c == ' ' || c == '\t');
        }

        bool is_symbol(char c)
        {
            return (c == '+' || c == '-' || c == '*' || c == '/' || c == '#' || c == '^');
        }


        bool is_paranthesis(char c)
        {
            return (c == '(' || c == ')' || c == '[' || c == ']');
        }

        bool is_digit(char c)
        {
            for (int i = 0; i < expresie.size(); ++i)
            {
                char c = expresie[i];

                if (c < '0' || c > '9')
                {
                    return false;
                }
                return true;
            }
        }
        bool is_radical(char c)
        {
            return (c == '#');
        }
        bool is_digit_or_symbol_or_space(char c)
        {
            return (is_paranthesis(c) || is_digit(c) || is_symbol(c) || is_space(c) || is_radical(c));
        }


    };

    class Calculator
    {
    private:
        map<string, double> variabile;

    public:

        void adaugaVariabila(const string& nume, double valoare) {
            variabile[nume] = valoare;
        }
        double getValoareVariabila(const string& nume) {
            auto it = variabile.find(nume);
            if (it != variabile.end()) {
                return it->second;
            }
            else {
                cout << "Variabila " << nume << " nu exista.\n";
                return 0.0;  
            }
        }

        ValidareString validator;
        static const int MAX_VARIABLES = 100;
        string variableNames[MAX_VARIABLES];
        double variableValues[MAX_VARIABLES];
        int numVariables = 0;
        void salveazaRezultatInFisier() const {
            ofstream outFile("result.bin", ios::binary | ios::trunc);
            if (outFile.is_open()) {
                outFile.write(reinterpret_cast<const char*>(&ultimulRez), sizeof(ultimulRez));
                outFile.close();
            }
            else {
                cout << "Eroare la deschiderea fisierului pentru salvare.\n";
            }
        }

        void citesteRezultatDinFisier() {
            ifstream inFile("result.bin", ios::binary);
            if (inFile.is_open()) {
                inFile.read(reinterpret_cast<char*>(&ultimulRez), sizeof(ultimulRez));
                inFile.close();
                cout << "Rezultatul a fost citit cu succes din fisierul result.bin.\n";
            }
            else {
                cout << "Eroare la deschiderea fisierului pentru citire.\n";
            }
        }
        double ultimulRez;

        void setultimulRez(double result) {
            ultimulRez = result;
        }

        double getultimulRez() {
            return ultimulRez;
        }

        string getExpresie() {
            return validator.getExpresie();
        }
        Calculator& operator=(const Calculator& other) {
            if (this != &other) {

                this->validator = other.validator;
            }
            return *this;
        }

        bool operator<(const Calculator& other) const {
            return validator.getExpresie() < other.validator.getExpresie();
        }


        friend ostream& operator<<(ostream& os, const Calculator& calculator);
        friend istream& operator>>(istream& is, Calculator& calculator);

        double calculRadical(double base, double radical)
        {
            return pow(base, 1.0 / radical);
        }

        double calculeazaExpresie(const string& expresie)
        {
            validator.setExpresie(expresie);

            if (validator.valideaza_expresia())
            {
                double numar1 = validator.getNumar1();
                double numar2 = validator.getNumar2();
                char operatie = validator.getOperator();

                switch (operatie)
                {
                case '+':
                    return numar1 + numar2;
                case '-':
                    return numar1 - numar2;
                case '*':
                    return numar1 * numar2;
                case '/':
                    if (numar2 != 0.0)
                    {
                        return numar1 / numar2;
                    }
                    else
                    {
                        cout << "Impartire la zero!" << endl;
                        return 0.0;
                    }
                case '^':
                    return ridicareLaPutere(numar1, numar2);
                case '#':
                    return calculRadical(numar1, numar2);
                default:
                    cout << "Operator invalid!" << endl;
                    return 0.0;
                }
            }
            else
            {
                cout << "Expresie nevalida!" << endl;
                return 0.0;
            }
        }


    private:

        double ridicareLaPutere(double baza, double exponent)
        {
            double rezultatP = 1.0;
            for (int i = 0; i < exponent; i++)
            {
                rezultatP *= baza;
            }
            return rezultatP;
        }
        friend   ostream& operator<<(ostream& os, const Calculator& calculator) {
            os << "Expresie: " << calculator.validator.getExpresie();
            return os;
        }

        friend   istream& operator>>(istream& in, Calculator& calculator) {
            return in;
        }
    };

    class Parser
    {
    public:
        bool operator>(const Parser& other) const {
            return expression > other.expression;
        }
        friend ostream& operator<<(ostream& os, const Parser& parser);
        friend istream& operator>>(istream& is, Parser& parser);
        Parser(const string& expr) : expression(expr), pozCurenta(0) {}

        double parseExpression()
        {
            return parseAdunareScadere();
        }

    private:
        Calculator calculator;
        const string& expression;
        size_t pozCurenta;
        bool is_radical(char c)
        {
            return (c == '#');
        }
        char getCurrentChar()
        {
            if (pozCurenta < expression.size()) {
                return expression[pozCurenta];
            }
            else {
                return '\0';
            }
        }

        void consumeChar()
        {
            if (pozCurenta < expression.size()) {
                pozCurenta++;
            }
        }

        bool isClosingParenthesis(char open, char close)
        {
            return (open == '(' && close == ')') || (open == '[' && close == ']');
        }

        double parsePrimary()
        {

            string varName;
            char currentChar = getCurrentChar();
            while (isalpha(currentChar)) {
                varName += currentChar;
                consumeChar();
                currentChar = getCurrentChar();
            }

            for (int i = 0; i < calculator.numVariables; i++) {
                if (calculator.variableNames[i] == varName) {
                    return calculator.variableValues[i];
                }
            }

            if (currentChar == '(' || currentChar == '[')
            {
                char openingParenthesis = currentChar;
                consumeChar();
                double result = parseAdunareScadere();

                currentChar = getCurrentChar();
                if (currentChar == ')' || currentChar == ']')
                {
                    char closingParenthesis = currentChar;
                    consumeChar();

                    if (!isClosingParenthesis(openingParenthesis, closingParenthesis))
                    {
                        cout << "Parantezele nu se inchid corect!" << endl;
                        return 0.0;
                    }
                }
                else
                {
                    cout << "Parantezele nu se inchid corect!" << endl;
                    return 0.0;
                }

                return result;
            }
            else if (isdigit(currentChar) || currentChar == '.')
            {
                return parseNumber();
            }

            else
            {
                cout << "Expresie nevalida!" << endl;
                return 0.0;
            }

        }
        double parseRadical()
        {
            double base = parsePrimary();
            char currentChar = getCurrentChar();

            if (is_radical(currentChar))
            {
                consumeChar();
                double radical = parsePrimary();
                return calculator.calculRadical(base, radical);
            }
            else
            {
                return base;
            }
        }
        double parseExponentiation()
        {
            double leftOperand = parseRadical();
            char currentChar = getCurrentChar();

            while (currentChar == '^') {
                consumeChar();
                double rightOperand = parseRadical();
                leftOperand = pow(leftOperand, rightOperand);
                currentChar = getCurrentChar();
            }

            return leftOperand;
        }



        double parseNumber()
        {

            string numberStr;
            char currentChar = getCurrentChar();
            bool gasitPunct = false;



            while (isdigit(currentChar) || currentChar == '.' || currentChar == ',')
            {
                if (currentChar == '.' || currentChar == ',')
                {
                    if (gasitPunct)
                    {
                        cout << "eroare, numarul contine mai mult de un punct/virgula" << endl;
                        return 0.0;
                    }
                    gasitPunct = true;
                    numberStr += '.';
                }
                else
                {
                    numberStr += currentChar;
                }

                consumeChar();
                currentChar = getCurrentChar();
            }

            if (numberStr.empty())
            {
                cout << "Error, the number is not valid." << endl;
                return 0.0;
            }


            try
            {
                return stod(numberStr);
            }
            catch (const invalid_argument& e)
            {
                cout << "Eroare, string invalid: " << numberStr << endl;
                return 0.0;
            }


            while (isdigit(currentChar) || currentChar == '.') {
                numberStr += currentChar;
                consumeChar();
                currentChar = getCurrentChar();
            }

            try {
                return stod(numberStr);
            }
            catch (const invalid_argument& e) {
                cout << "Eroare, string invalid" << numberStr << endl;
                return 0.0;
            }
        }



        double parseInmultireImpartire()
        {
            double leftOperand = parseExponentiation();
            char currentChar = getCurrentChar();

            while (currentChar == '*' || currentChar == '/') {
                char operation = currentChar;
                consumeChar();
                double rightOperand = parseExponentiation();

                if (operation == '*') {
                    leftOperand *= rightOperand;
                }
                else {
                    if (rightOperand != 0.0) {
                        leftOperand /= rightOperand;
                    }
                    else {
                        cout << "Impartire la zero!" << endl;
                        return 0.0;
                    }
                }

                currentChar = getCurrentChar();
            }

            return leftOperand;
        }


        double parseAdunareScadere()
        {
            double leftOperand = parseInmultireImpartire();
            char currentChar = getCurrentChar();

            while (currentChar == '+' || currentChar == '-') {
                char operation = currentChar;
                consumeChar();
                double rightOperand = parseInmultireImpartire();

                if (operation == '+') {
                    leftOperand += rightOperand;
                }
                else {
                    leftOperand -= rightOperand;
                }

                currentChar = getCurrentChar();
            }

            return leftOperand;
        }

        friend  istream& operator>>(istream& is, Parser& parser) {
            cout << "Introduceti o expresie: ";

            return is;
        }

        friend ostream& operator<<(ostream& os, const Parser& parser) {
            os << "Expresie: " << parser.expression;
            return os;
        }
    };

    class UserInterface {
    public:

        void introducereEcuatie(Calculator& calculator) {
            string expression;
            cout << "Introduceti o expresie matematica: ";
            getline(cin, expression);

            string expresieFaraSpatii;
            for (int i = 0; i < expression.size(); ++i) {
                if (expression[i] != ' ') {
                    expresieFaraSpatii += expression[i];
                }
            }

            expression = expresieFaraSpatii;
            Parser parser(expression);
            double result = parser.parseExpression();
            calculator.ultimulRez = result; 

            cout << "Rezultatul expresiei este: " << fixed << result << endl;

            calculator.salveazaRezultatInFisier();
        }

    
        void salveazaRezultatCurent(Calculator& calculator) {
            ofstream outFile("results.bin", ios::trunc);
        
            if (!outFile) {
                cout << "Nu s-a putut deschide fișierul!";
                return;
            }

            double result = calculator.getultimulRez();
            outFile.write(reinterpret_cast<const char*>(&result), sizeof(result));

            outFile.close();

            cout << "Rezultatul a fost salvat cu succes.\n";
        }

        double citesteRezultatCurent() {
            double result;

            ifstream inFile("results.bin", ios::binary);

            if (!inFile) {
                cout << "Unable to open file!";
                return 0.0;
            }

            inFile.read(reinterpret_cast<char*>(&result), sizeof(result));

            inFile.close();

            cout << "The result has been read successfully.\n";

            return result;
        }

        void afiseazaVariabilaDinFisier(Calculator& calculator) {
            ifstream inFile("result.bin", ios::binary);

            if (inFile.is_open()) {
                inFile.read(reinterpret_cast<char*>(&calculator.ultimulRez), sizeof(calculator.ultimulRez));

                inFile.close();

                cout << "Rezultatul citit din fisierul result.bin este: " << fixed << calculator.ultimulRez << "\n";
            }
            else {
                cout << "Eroare la deschiderea fisierului pentru citire.\n";
            }
        }

        void procesareEcuatiiDinFisier() {
            ifstream inFile("C:\\Users\\Doru\\Desktop\\OOP\\x64\\Debug\\equations.txt");
            
            if (!inFile) {
                cout << "Unable to open file!";
            }

            Calculator calculator;

            string equation;
            while (getline(inFile, equation)) {
                Parser parser(equation);
                double result = parser.parseExpression();
                calculator.ultimulRez = result;  

                cout << "Rezultatul expresiei " << equation << " este: " << result << endl;
            }

            inFile.close();
            return;
        }

       
    };

    class CalculatorStiintific : public Calculator
    {
    public:
        CalculatorStiintific() : Calculator() {}

        double my_sin(double angle) {
            return sin(angle);
        }

        double my_cos(double angle) {
            return cos(angle);
        }

        double my_tan(double angle) {
            return my_tan(angle);
        }

        double my_log(double value) {
            if (value <= 0.0) {
                cout << "Eroare: Argumentul pentru logaritmul natural trebuie să fie mai mare decât 0.\n";
                return 0.0;
            }
            return log(value);
        }

        double my_log10(double value) {
            if (value <= 0.0) {
                cout << "Eroare: Argumentul pentru logaritmul în baza 10 trebuie să fie mai mare decât 0.\n";
                return 0.0;
            }
            return log10(value);
        }
    };

    
    void afisareMeniuCalculatorStiintific() {
         cout << "7. Calcul sin\n";
         cout << "8. Calcul cos\n";
         cout << "9. Calcul tg\n";
         cout << "10. Calcul log\n";
         cout << "11. Calcul log10\n";
    }
    int main(int argc, char* argv[]) {
        UserInterface ui;
        CalculatorStiintific calculator;
        double result = 0.0;

        if (argc > 1) {
            string equation = argv[1];
            Parser parser(equation);
            result = parser.parseExpression();
            cout << "Rezultatul expresiei " << equation << " este: " << result << endl;
        }
        else {
            int optiune = 0;
            while (true) {
                cout << "Meniu:\n";
                cout << "1. Introducere ecuatie\n";
                cout << "2. Salveaza rezultat curent intr-o variabila\n";
                cout << "3. Foloseste valoarea din fisier pentru o operatie\n";
                cout << "4. Procesare ecuatii din fisier\n";
                cout << "5. Afisare Meniu Calculator Stiintific\n";
                cout << "6. Iesire\n";
                cout << "Alegeti o optiune: ";
                cin >> optiune;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                switch (optiune) {
                case 1:
                    ui.introducereEcuatie(calculator);
                    break;
                case 2:
                    ui.salveazaRezultatCurent(calculator);
                    break;
                case 3:
                    ui.afiseazaVariabilaDinFisier(calculator);
                    double operand;
                    cout << "Introduceti operandul pentru operatia curenta: ";
                    cin >> operand;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    char operation;
                    cout << "Introduceti operatorul (+, -, *, /, ^, #): ";
                    cin >> operation;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    switch (operation) {
                    case '+':
                        result = calculator.getultimulRez() + operand;
                        break;
                    case '-':
                        result = calculator.getultimulRez() - operand;
                        break;
                    case '*':
                        result = calculator.getultimulRez() * operand;
                        break;
                    case '/':
                        if (operand != 0.0) {
                            result = calculator.getultimulRez() / operand;
                        }
                        else {
                            cout << "Impartire la zero!\n";
                            result = 0.0;
                        }
                        break;
                    case '^':
                        result = pow(calculator.getultimulRez(), operand);
                        break;
                    case '#':
                        result = calculator.calculRadical(calculator.getultimulRez(), operand);
                        break;
                    default:
                        cout << "Operator invalid!\n";
                        result = 0.0;
                    }
                    cout << "Rezultatul operatiei este: " << fixed << result << "\n";
                    break;
                case 4:
                    ui.procesareEcuatiiDinFisier();
                    break;
                case 5:
                    afisareMeniuCalculatorStiintific();
                    int optiuneStiintifica;
                    cout << "Alegeti o operatie stiintifica: ";
                    cin >> optiuneStiintifica;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');

                    switch (optiuneStiintifica) {
                    case 7:
                        cout << "Introduceti un unghi in radiani: ";
                        double unghi;
                        cin >> unghi;
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << "Sinusul unghiului este: " << calculator.my_sin(unghi) << "\n";
                        break;
                    case 8:
                        cout << "Introduceti un unghi in radiani: ";
                        cin >> unghi;
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << "Cosinusul unghiului este: " << calculator.my_cos(unghi) << "\n";
                        break;
                    case 9:
                        cout << "Introduceti un unghi in radiani: ";
                        cin >> unghi;
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << "mytangenta unghiului este: " << calculator.my_tan(unghi) << "\n";
                        break;
                    case 10:
                        double valoare;
                        cout << "Introduceti o valoare pozitiva pentru calculul logaritmului natural: ";
                        cin >> valoare;
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << "Logaritmul natural al valorii este: " << calculator.my_log(valoare) << "\n";
                        break;
                    case 11:
                        cout << "Introduceti o valoare pozitiva pentru calculul logaritmului in baza 10: ";
                        cin >> valoare;
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << "Logaritmul in baza 10 al valorii este: " << calculator.my_log10(valoare) << "\n";
                        break;
                    default:
                        cout << "Optiune stiintifica invalida. Incercati din nou.\n";
                    }
                    break;
                case 6:
                    cout << "Pa";
                    return 0;
                default:
                    cout << "Optiune invalida. Incercati din nou.\n";
                }
            }
        }

        return 0;
    }
