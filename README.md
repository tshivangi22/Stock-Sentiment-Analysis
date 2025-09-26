"# Stock Sentiment Analysis Project" 
# Stock Sentiment Analysis Project

## Project Overview

This project analyzes stock price data using sentiment analysis combined with technical indicators and machine learning to develop and evaluate trading strategies.

### Workflow Summary

1. **Initial C++ Implementation**  
   - Developed basic C++ code to process stock OHLCV data.  
   - Computed fundamental features and assigned initial sentiment labels based on predefined rules.

2. **Technical Indicators and Enhanced Sentiment (Python)**  
   - Calculated technical indicators like moving averages, RSI, MACD, and Bollinger Bands using Python.  
   - Enhanced the original sentiment labeling using these indicators for improved market insight.  
   - Backtested both original and enhanced sentiment strategies and found enhanced sentiment yielded better returns.

3. **Machine Learning Model Integration**  
   - Trained an XGBoost model to predict sentiment-based trading signals, achieving strong initial performance.  
   - Addressed overfitting concerns by switching to a Random Forest classifier, which provided more robust, generalizable results.

4. **Risk Management via Stop-Loss**  
   - Implemented stop-loss logic to minimize losses during unfavorable market movements.  
   - Applied stop-loss to the ML-based strategy and evaluated its impact.

5. **Comparative Analysis**  
   - Conducted a comprehensive comparison of all three strategies (Original Sentiment, Enhanced Sentiment, and ML-predicted Sentiment).  
   - Evaluated performance using metrics like total returns and holding times.

## Project Files / Notebook Access

- **View in GitHub (may not show outputs):**
  [Stock DSA part Notebook](stock_dsa_ml.ipynb)

- **Download full notebook with outputs (Google Drive link):**
  [Download/see DSA part Notebook](https://colab.research.google.com/drive/1Akldz5U-EdNMkWAO-7xDyYkRjoG54jag?usp=sharing)

- **View in GitHub (may not show outputs):**
  [Stock Sentiment Analysis ML part Notebook](ml_part.ipynb)

- **Download full notebook with outputs (Google Drive link):**
  [Download/see ML part Notebook](https://colab.research.google.com/drive/1JOfGKZeZAqPW13UusHrKa6K21lNILfCN?usp=sharing)

### Key Results (Approximate)

- Enhanced sentiment strategy outperformed the original sentiment baseline in backtesting.  
- ML-predicted sentiment (Random Forest) improved prediction accuracy and trade performance, reducing overfitting risk compared to XGBoost.  
- Adding stop-loss further helped control downside risk and improved risk-adjusted returns.

## Technologies Used

- **C++** for data preprocessing and basic sentiment logic.  
- **Python** (with Pandas, numpy, sklearn, XGBoost) for feature engineering, ML modeling, backtesting, and visualization.  
- **Jupyter Notebooks** for interactive analysis and model training.
