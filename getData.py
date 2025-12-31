import pandas as pd
import yfinance as yf



def get_sp500_close_prices(start, end):
    """
    Downloads daily closing prices for all S&P 500 stocks.
    Returns a DataFrame indexed by date with tickers as columns.
    """
    tickers = {
        'AAPL','MSFT','AMZN','NVDA','GOOGL','GOOG','META','TSLA','JPM',
        'JNJ','V','XOM','PG','MA','HD','CVX','ABBV','LLY','AVGO',
        'PEP','COST','KO','MRK','BAC','WMT','DIS','CSCO','ACN','ABT',
        'ADBE','CRM','MCD','PFE','DHR','INTC','TXN','VZ','TMO','CMCSA',
        'NFLX','AMD','QCOM','PM','UNH','NEE','LIN','LOW','UPS','BMY'
    }
  # Example subset of tickers for demonstration

    data = yf.download(
        tickers,
        start=start,
        end=end,
        auto_adjust=False,
        progress=True
    )

    # Extract Close prices
    close_prices = data['Close']

    return close_prices


if __name__ == "__main__":
    start_date = "2015-01-01"
    end_date = "2025-01-01"

    close_df = get_sp500_close_prices(start_date, end_date)
    close_df.to_csv("close_prices.csv")
    print(close_df.head())
    print(close_df.shape)
