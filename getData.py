import pandas as pd
import yfinance as yf


def get_sp500_tickers():
    """
    Fetches the list of S&P 500 tickers from Wikipedia.
    """
    url = "https://en.wikipedia.org/wiki/List_of_S%26P_500_companies"
    tables = pd.read_html(url)
    sp500_table = tables[0]

    tickers = sp500_table['Symbol'].tolist()

    # Yahoo Finance uses '-' instead of '.' for some tickers
    tickers = [ticker.replace('.', '-') for ticker in tickers]

    return tickers


def get_sp500_close_prices(start, end):
    """
    Downloads daily closing prices for all S&P 500 stocks.
    Returns a DataFrame indexed by date with tickers as columns.
    """
    tickers ={'AAPL', 'MSFT', 'GOOGL', 'AMZN', 'NFLX','META'}  # Example subset of tickers for demonstration

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
