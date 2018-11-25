#include "wordprediction.h"

using namespace std;

class ExampleCallback : public PresageCallback
{
public:
    ExampleCallback(const std::string& _past_context) : past_context(_past_context) { }

    std::string get_past_stream() const { return past_context; }
    std::string get_future_stream() const { return empty; }

private:
    const std::string& past_context;
    const std::string empty;

};

LedKeyboard::KeyValueArray keyArray(27);


int getKey(char c) {
    int index = -1;
    if(c ==39) {
        index = 26;
    }
    else if ('A' <= c && c <= 'Z') {
        index = c - 'A';
    }
    else if ('a' <= c && c <= 'z') {
        index = c - 'a';
    }
    return index;
}

int lightWord(LedKeyboard &kbd, std::string word) {
    uint8_t index;
    kbd.setAllKeys(backgroundColor);
    if(! kbd.commit()) return 1;
    for (int i = 0; i < word.length() && i < 4; i++) {
        index = getKey(word[i]);
        if (index >= 0) {
            keyArray[index].color = predictionColor;
            
            keyArray[index].color.red -= i * 50;
            keyArray[index].color.green -= i * 50;
            keyArray[index].color.blue -= i * 50;

            if(! kbd.setKey(keyArray[index])) return 1;
            if(! kbd.commit()) return 1;

        }
    }
}

int wordprediction(LedKeyboard &kbd)
{
    std::string context;
    ExampleCallback callback(context);
    Presage presage(&callback);

    if (! kbd.open()) return 1;
    kbd.setAllKeys(backgroundColor);
    if(! kbd.commit()) return 1;

    
    for (uint i=0; i < keyArray.size(); i++) {

        LedKeyboard::Key key;
        
        std::string token;
        if(i == 26) {
            token = '"';
        }
        else {
            token = 'a' + i;
        }
        if (! utils::parseKey(token, key)) return 1;
        keyArray[i] = { key, backgroundColor };
    }


    string predWord;
    string prediction;
    system("stty raw"); 

    char c;
    for (;;) {
        // prompt user and append line into context buffer
        
        c = cin.get();
        if (c == ' ') {
            context = "";
        }

        context.push_back(c);
        // request prediction
        if (presage.predict().empty()) {
            cout << "no suggestion available" << endl;
            kbd.setAllKeys(backgroundColor);
            if(! kbd.commit()) return 1;
            continue;
        }
        prediction = presage.predict()[0];
        
        // print predictions
        cout <<"\n     suggest: " << prediction;

        if (prediction.length() > context.length()) {
            predWord = prediction.substr(context.length());
            lightWord(kbd, predWord);
        }
    
        
    }

    return 0;
}
