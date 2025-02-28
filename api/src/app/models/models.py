from sqlalchemy.ext.declarative import declarative_base
from sqlalchemy.sql import func
from sqlalchemy import Column, Integer, Float, String, DateTime 

Base = declarative_base()
#is datetime a type in js?
class TemperatureData(Base):
    __tablename__ = "tempdata"

    id = Column(Integer, primary_key=True, index=True, nullable=False)
    temperature = Column(Float, index=True, nullable=False)
    door_status = Column(String, index=True, nullable=False)
    timestamp = Column(DateTime, default=func.now(), nullable=False)