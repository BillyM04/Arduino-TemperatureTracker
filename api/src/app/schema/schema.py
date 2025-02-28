from pydantic import BaseModel
from datetime import datetime
from typing import Optional

class TemperatureDataIn(BaseModel):
    temperature: float
    door_status: str

    class Config:
        orm_mode = True


class TemperatureDataOut(TemperatureDataIn):
    id: Optional[int]
    timestamp: Optional[datetime]

    class Config:
        orm_mode = True