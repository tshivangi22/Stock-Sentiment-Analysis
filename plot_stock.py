import pandas as pd
import mplfinance as mpf

# Step 1: Read CSV
df = pd.read_csv("enhanced_stock_dataset.csv")

# Step 2: Convert Date column to datetime format
df['Date'] = pd.to_datetime(df['Date'])

# Step 3: Set 'Date' as index (required for mplfinance)
df.set_index('Date', inplace=True)

# Step 4: Filter only required OHLCV columns
df = df[['Open', 'High', 'Low', 'Close', 'Volume']]

# Step 5: Plot candlestick chart with 3 and 10-day moving averages
mpf.plot(
    df,
    type='candle',
    style='charles',
    mav=(3, 10),               # Moving averages
    volume=True,               # Show volume subplot
    title='Candlestick Chart with MA(3) & MA(10)',
    ylabel='Stock Price',
    ylabel_lower='Volume',
    figratio=(12, 6),
    figscale=1.2
)


