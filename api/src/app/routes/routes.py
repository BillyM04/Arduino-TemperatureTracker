from fastapi import APIRouter, Depends, HTTPException, Request, Response, BackgroundTasks
from sqlalchemy import func
from sqlalchemy.orm import Session
from src.app.database.database import get_db
from src.app.models.models import TemperatureData
from src.app.schema.schema import TemperatureDataIn, TemperatureDataOut
from typing import List


v1 = APIRouter()
recieved_data = []
threshold = 20


#function to upload to db
def backgroundUpload(db: Session):
    for entry in recieved_data:
        new_data = TemperatureData(**entry)
        db.add(new_data)

    db.commit()  
    sent_data = recieved_data.copy()
    recieved_data.clear() 
    return {
        "status": 200,
        "data_stored": sent_data
        }

#root verification
@v1.get("/")
async def readRoot():
    return {"message": "FastAPI server is running"}

#post request from retrieveData.cpp
@v1.post("/serial-data")
async def readData(data: TemperatureDataIn, background_tasks: BackgroundTasks, db: Session = Depends(get_db)):
    recieved_data.append(data.__dict__)
    # print(len(recieved_data))

    #if size of recieved data is too much, the data will be sent and list will be cleared
    if len(recieved_data) >= threshold:
        background_tasks.add_task(backgroundUpload, db)

    return Response(content="application/json", status_code=200)

#post request to database
@v1.post("/temp-data")
async def postData(db: Session = Depends(get_db)):
    if len(recieved_data) < threshold:
        return {
            "status": 400,
            "message": f"Not enough data to store. Current count: {len(recieved_data)}",
            }

    elif len(recieved_data) >= threshold:
        for entry in recieved_data:
            new_data = TemperatureData(**entry)
            db.add(new_data)

        db.commit()  
        sent_data = recieved_data.copy()
        recieved_data.clear() 

        return {
            "status": 200,
            "data_stored": sent_data
            }

#get request for db from frontend
@v1.get("/temp-data", response_model=List[TemperatureDataOut])
async def getData(db: Session = Depends(get_db), limit: int = 20):
    data = db.query(TemperatureData).order_by(TemperatureData.timestamp.desc()).limit(limit).all()
    return data

