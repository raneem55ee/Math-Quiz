
#include <iostream>
#include<cstdlib>
using namespace std;

enum enQuestionsLevel { EasyLevel = 1, MedLevel, HardLevel, MixLevel };
enum enOpType         { Add = 1, Sub, Mult, Div, MixOp };

struct stQuestion {

    int firstNum = 0;
    int secondNum = 0;
    enQuestionsLevel questionLevel;
    enOpType opType;
    int playerAnswer = 0;
    int rightAnswer = 0;
    bool answerResult = false;

};

struct stQuizz {

    stQuestion questionsList[100];
    short numOfQuestions = 0;
    enQuestionsLevel questionsLevel;
    enOpType opType;
    short numOfRightAnswers = 0;
    short numOfWrongAnswers = 0;
    bool isPass = false;

};

int RandomNumber(int from, int to) {

    return (rand() % (to - from + 1) + from);
}

enQuestionsLevel ReadQuestionsLevel() {

    unsigned short questionsLevel;

    do {

        cout << "Enter quiz level=>  [1]Easy, [2]Med, [3]Hard, [4]Mix: ";
        cin >> questionsLevel;

        cout << endl;

    } while (questionsLevel < 1 || questionsLevel>4);

    cout << endl;

    return (enQuestionsLevel)questionsLevel;

}

enOpType ReadOpType() {

    unsigned short opType;

    do {

        cout << "Enter operation type=>  [1]Add, [2]Sub, [3]Mul, [4]Div, [5]Mix: ";
        cin >> opType;

        cout << endl;

    } while (opType < 1 || opType>5);

    cout << endl << endl;

    return (enOpType)opType;

}

string GetQuizLevelName(enQuestionsLevel questionsLevel) {

    string levels[4] = { "Easy","Med","Hard","Mix" };

    return levels[questionsLevel - 1];

}

string GetOpTypeName(enOpType opType) {

    string operationsName[5] = { "Add","Sub","Mult","Div","Mix" };

    return operationsName[opType - 1];

}

enOpType GetRandomOpType() {

    return (enOpType)RandomNumber(1, 4);

}

short ReadHowManyQuestions() {

    int numOfQuestions;

    do {

        cout << "How may questions do you want to answer? From 1 to 20: ";
        cin >> numOfQuestions;
        cout << endl;

    } while (numOfQuestions < 1 || numOfQuestions > 20);

    return (short)numOfQuestions;

}

void ResetScreen() {

    system("cls");
    system("color 0F");

}

void SetScreenColor(bool answerResult) {

    if (answerResult) {

        system("color 2F");

    }
    else {

        system("color 4F");
        cout << '\a';

    }
   
}

int ReadQuestionAnswer() {

    int ans;

    cin >> ans;

    return ans;

}

string GetOpTypeSymbol(enOpType opType) {

    string operation[4] = { "+","-","*","/" };

    return operation[opType - 1];

}

void PrintTheQuestion(stQuizz quiz, int questionNum) {

    cout << "Question [" << questionNum+1 << "/" << quiz.numOfQuestions << "] \n\n";
    cout << quiz.questionsList[questionNum].firstNum << endl;
    cout << quiz.questionsList[questionNum].secondNum << " "
        << GetOpTypeSymbol(quiz.questionsList[questionNum].opType) << endl;

    cout << "_____________________\n";

}

void CorrectTheQuestionAnswer(stQuizz& quiz, int questionNum) {

    if (quiz.questionsList[questionNum].rightAnswer != quiz.questionsList[questionNum].playerAnswer) {

        quiz.questionsList[questionNum].answerResult = false;
        quiz.numOfWrongAnswers++;

        cout << "Wrong Answer :-(\n";
        cout << "The right answer is " << quiz.questionsList[questionNum].rightAnswer << endl ;

    }

    else {

        quiz.questionsList[questionNum].answerResult = true;
        quiz.numOfRightAnswers++;

        cout << "Right Answer :-)\n";
        
    }
    
    cout << endl;

    SetScreenColor(quiz.questionsList[questionNum].answerResult);

}

void AskAndCorrectQuestionListAnswers(stQuizz& quiz) {

    for (int questionNum = 0; questionNum < quiz.numOfQuestions; questionNum++) {

        PrintTheQuestion(quiz, questionNum);

        quiz.questionsList[questionNum].playerAnswer = ReadQuestionAnswer();

        CorrectTheQuestionAnswer(quiz, questionNum);

    }

    quiz.isPass = quiz.numOfRightAnswers >= quiz.numOfWrongAnswers;

}

int SimpleCalculator(int number1, int number2, enOpType opType) {

    switch (opType) {

    case (enOpType::Add):
        return number1 + number2;
    case (enOpType::Sub):
        return number1 - number2;
    case (enOpType::Mult):
        return number1 * number2;
    case (enOpType::Div):
        return number1 / number2;
    default:
        return number1 + number2;
    }

}

stQuestion GenerateQuestion(enQuestionsLevel questionLevel, enOpType opType){
 

     stQuestion question;

     if (questionLevel == enQuestionsLevel::MixLevel) {

         questionLevel = (enQuestionsLevel)RandomNumber(1, 3);

     }

     if (opType == enOpType::MixOp) {

         opType = GetRandomOpType();

     }

     question.opType = opType;

     switch (questionLevel) {

     case(enQuestionsLevel::EasyLevel):
         question.firstNum = RandomNumber(1, 10);
         question.secondNum = RandomNumber(1, 10);
         
         question.rightAnswer = SimpleCalculator(question.firstNum, question.secondNum, question.opType);
         question.questionLevel = questionLevel;

         return question;

     case(enQuestionsLevel::MedLevel):
         question.firstNum = RandomNumber(10,50);
         question.secondNum = RandomNumber(10, 50);

         question.rightAnswer = SimpleCalculator(question.firstNum, question.secondNum, question.opType);
         question.questionLevel = questionLevel;

         return question;

     case(enQuestionsLevel::HardLevel):
         question.firstNum = RandomNumber(50, 100);
         question.secondNum = RandomNumber(50, 100);

         question.rightAnswer = SimpleCalculator(question.firstNum, question.secondNum, question.opType);
         question.questionLevel = questionLevel;

         return question;
     }

     return question;

 }

void GenerateQuizQuestions(stQuizz& quiz) {

    for (int question = 0; question < quiz.numOfQuestions; question++) {

        quiz.questionsList[question] = GenerateQuestion(quiz.questionsLevel, quiz.opType);
    }

}

string GetFinalResultText(bool pass) {

    if (pass)
        return "PASS :)";
   
    return "FAIL :(";

}

void PrintQuizResults(stQuizz quiz) {

    cout << "\n_______________________________________\n";
    cout << "Final Result Is " << GetFinalResultText(quiz.isPass) << endl;
    cout << "_______________________________________\n";

    cout << "Number of questions     : " << quiz.numOfQuestions << endl;
    cout << "Questions level         : " << GetQuizLevelName(quiz.questionsLevel) << endl;
    cout << "Op type                 : " << GetOpTypeName(quiz.opType) << endl;
    cout << "Number of right answers : " << quiz.numOfRightAnswers<< endl;
    cout << "Number of wrong answers : " << quiz.numOfWrongAnswers << endl;

    cout << "___________________________________________________\n";

}

void PlayMathGame() {

    stQuizz quiz;

    quiz.numOfQuestions = ReadHowManyQuestions();
    quiz.questionsLevel = ReadQuestionsLevel();
    quiz.opType = ReadOpType();

    GenerateQuizQuestions(quiz);
    AskAndCorrectQuestionListAnswers(quiz);
    PrintQuizResults(quiz);

}

void StartQuiz() {

    char playAgain = 'Y';

    do {

        ResetScreen();

        PlayMathGame();

        cout << "Do you want to do the quiz again? (y/n)? ";
        cin >> playAgain;

    } while (playAgain == 'Y' || playAgain == 'y');
}

int main()
{
    srand((unsigned)time(NULL));

    StartQuiz();

	return 0;
}