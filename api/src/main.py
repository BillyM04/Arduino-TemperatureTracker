from fastapi import FastAPI
from fastapi.middleware.cors import CORSMiddleware
from src.app.routes.routes import v1
import os
from dotenv import load_dotenv

load_dotenv()

IP = os.getenv('FRONT_IP')

app = FastAPI()

origins = [
    "http://localhost:3000",  
    IP,  
]

app.add_middleware(
    CORSMiddleware,
    allow_origins=origins, 
    allow_credentials=True,
    allow_methods=["*"], 
    allow_headers=["*"],  
)

app.include_router(v1, prefix="/v1")