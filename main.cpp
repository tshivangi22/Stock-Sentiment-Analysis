#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;

struct StockData {
    string date;
    double open, high, low, close;
    long volume;
    double dailyReturn, volatility, volumeMA;
    string sentiment;
    
    double closeMA3;
    double closeMA5;
    double closeMA10;
};


vector<StockData> readCSV(const string& filename) {
    vector<StockData> data;
    ifstream file(filename);
    string line, word;

    getline(file, line); // Skip header

    while (getline(file, line)) {
        stringstream ss(line);
        StockData entry;
        string volume_str;

        getline(ss, entry.date, ',');
        getline(ss, word, ','); entry.open = stod(word);
        getline(ss, word, ','); entry.high = stod(word);
        getline(ss, word, ','); entry.low = stod(word);
        getline(ss, word, ','); entry.close = stod(word);
        getline(ss, volume_str, ','); entry.volume = stoll(volume_str);

        data.push_back(entry);
    }

    return data;
}
vector<double> calculateDailyReturns(const vector<StockData>& data) {
    vector<double> returns;
    for (size_t i = 1; i < data.size(); ++i) {
        double prevClose = data[i - 1].close;
        double currClose = data[i].close;
        double dailyReturn = (prevClose != 0) ? (currClose - prevClose) / prevClose : 0.0;
        returns.push_back(dailyReturn);
    }
    return returns;
}
vector<double> calculateIntradayVolatility(const vector<StockData>& data) {
    vector<double> volatility;
    for (const auto& entry : data) {
        double v = (entry.open != 0) ? (entry.high - entry.low) / entry.open : 0.0;
        volatility.push_back(v);
    }
    return volatility;
}
vector<double> calculateVolumeMovingAverage(const vector<StockData>& data, int window) {
    vector<double> ma;
    long long sum = 0;
    for (size_t i = 0; i < data.size(); ++i) {
        sum += data[i].volume;
        if (i >= window) {
            sum -= data[i - window].volume;
            ma.push_back((double)sum / window);
        } else if (i == window - 1) {
            ma.push_back((double)sum / window);
        }
    }
    return ma;
}
vector<string> labelSentiment(const vector<StockData>& data, const vector<double>& dailyReturns) {
    vector<string> sentiment;
    size_t offset = data.size() - dailyReturns.size(); // align with returns

    for (size_t i = 0; i < data.size(); ++i) {
        if (i < offset) {
            sentiment.push_back("Neutral"); // not enough data
            continue;
        }

        double ret = dailyReturns[i - offset];
        double ma3 = data[i].closeMA3;
        double ma10 = data[i].closeMA10;

        if (ret > 0.003 && ma3 > ma10)
        sentiment.push_back("Bullish");
        else if (ret < -0.003 && ma3 < ma10)
        sentiment.push_back("Bearish");
        else
        sentiment.push_back("Neutral");
    }
    int bullCount = 0, bearCount = 0, neutralCount = 0;
    for (const auto& s : sentiment) {
    if (s == "Bullish") bullCount++;
    else if (s == "Bearish") bearCount++;
    else neutralCount++;
   }
   cout << "Sentiment Counts:\nBullish: " << bullCount << "\nBearish: " << bearCount << "\nNeutral: " << neutralCount << endl;

    return sentiment;
}

vector<double> calculateCloseMovingAverage(const vector<StockData>& data, int window) {
    vector<double> ma;
    double sum = 0;
    for (size_t i = 0; i < data.size(); ++i) {
        sum += data[i].close;
        if (i >= window) {
            sum -= data[i - window].close;
            ma.push_back(sum / window);
        } else if (i == window - 1) {
            ma.push_back(sum / window);
        }
    }
    return ma;
}

void exportToCSV(const vector<StockData>& data,
                 const vector<double>& returns,
                 const vector<double>& volatility,
                 const vector<double>& volumeMA,
                 const vector<string>& sentiments,
                 const vector<double>& closeMA3,
                 const vector<double>& closeMA5,
                 const vector<double>& closeMA10,
                 const string& filename) {
    
    ofstream file(filename);
    
    // Write header
    file << "Date,Open,High,Low,Close,Volume,Return,Volatility,Volume_MA,Sentiment,CloseMA_3,CloseMA_5,CloseMA_10\n";

    size_t offset = data.size() - returns.size(); // to align shorter vectors

    for (size_t i = offset; i < data.size(); ++i) {
        file << data[i].date << ","
             << data[i].open << ","
             << data[i].high << ","
             << data[i].low << ","
             << data[i].close << ","
             << data[i].volume << ","
             << returns[i - offset] << ","
             << volatility[i] << ","
             << ((i >= 4) ? volumeMA[i - 4] : 0.0) << ","  // Volume MA starts from index 4 (5-day MA)
             << sentiments[i] << "," 
             << data[i].closeMA3 << ","
             << data[i].closeMA5 << "," 
             << data[i].closeMA10 << "\n";
    }

    file.close();
    cout << "Exported dataset to: " << filename << endl;
}


int main() {
    string filename = "trip.csv";
    vector<StockData> stockData = readCSV(filename);

    cout << "Loaded " << stockData.size() << " records.\n";
    cout << "Sample Entry: " << stockData[0].date << " | Close: " << stockData[0].close << endl;
    vector<double> dailyReturns = calculateDailyReturns(stockData);

    cout << "Sample return: " << dailyReturns[0] * 100 << "%" << endl;
    cout << "Computed " << dailyReturns.size() << " daily returns.\n";

    vector<double> volatility = calculateIntradayVolatility(stockData);
    cout << "Sample Volatility: " << volatility[0] * 100 << "%" << endl;

    vector<double> volumeMA = calculateVolumeMovingAverage(stockData, 5);
    cout << "5-day Avg Volume Sample: " << volumeMA[0] << endl;

    vector<double> closeMA3 = calculateCloseMovingAverage(stockData, 3);
    vector<double> closeMA5 = calculateCloseMovingAverage(stockData, 5);
    vector<double> closeMA10 = calculateCloseMovingAverage(stockData, 10);

    size_t maxOffset = stockData.size() - closeMA10.size(); // because 10-day MA is longest

       for (size_t i = 0; i < stockData.size(); ++i) {
    // 3-day Moving Average
    if (i >= 3) {
        stockData[i].closeMA3 = (
            stockData[i].close +
            stockData[i - 1].close +
            stockData[i - 2].close
        ) / 3.0;
    } else {
        stockData[i].closeMA3 = 0;
    }
    // if(i < 3)
    //  cout << "Index: " << i << ", MA3: " << stockData[i].closeMA3 << "\n";

    // 5-day Moving Average
    if (i >= 5) {
        stockData[i].closeMA5 = (
            stockData[i].close +
            stockData[i - 1].close +
            stockData[i - 2].close +
            stockData[i - 3].close +
            stockData[i - 4].close
        ) / 5.0;
    } else {
        stockData[i].closeMA5 = 0;
    }

    // 10-day Moving Average
    if (i >= 10) {
        double sum = 0;
        for (size_t j = i - 9; j <= i; ++j) {
            sum += stockData[j].close;
        }
        stockData[i].closeMA10 = sum / 10.0;
    } else {
        stockData[i].closeMA10 = 0;
    }
}
 
    vector<string> sentiments = labelSentiment(stockData, dailyReturns);
    cout << "First day sentiment: " << sentiments[0] << endl;

    exportToCSV(stockData, dailyReturns, volatility, volumeMA, sentiments,closeMA3,closeMA5,closeMA10, "enhanced_stock_dataset.csv");


    return 0;
}
