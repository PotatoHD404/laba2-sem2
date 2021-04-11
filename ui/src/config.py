from secrets import token_urlsafe

SECRET_KEY = token_urlsafe(64)
SESSION_TYPE = 'sqlalchemy'
SQLALCHEMY_DATABASE_URI = "sqlite:///test.db"
SQLALCHEMY_TRACK_MODIFICATIONS = False
SESSION_SQLALCHEMY_TABLE = 'sessions'
