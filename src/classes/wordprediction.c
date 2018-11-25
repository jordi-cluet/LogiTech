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

int main()
{
    std::string context;
    ExampleCallback callback(context);
    Presage presage(&callback);
    if (! kbd.open()) return 1;
    kbd.setAllKeys(defaultColor);
    if(! kbd.commit()) return 1;    
    initscr();
    
    std::string buffer;
    std::vector< std::string > predictions;

    for (;;) {
        // prompt user and append line into context buffer
        std::cout << "> ";
        getline(std::cin, buffer);
        context += buffer;

        // request prediction
        predictions = presage.predict ();

        // print predictions
        for (int i = 0; i < predictions.size(); i++) {
            std::cout << i << ':' << predictions[i] << std::endl;
        }
    }

    return 0;
}
