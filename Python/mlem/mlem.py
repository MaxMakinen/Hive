import json
import pathlib

from fastapi import fastAPI
from pydantic import Basemodel

app = FastAPI()

"""
@app.get("/")
def hello_world():
	return {"hello":"jerry"}

@app.get(
	"/showcase-features/{user_id}",
	summary="MY custom summary"
	description="MY cusotm descripton"
)

def showcase_features(
	user_id: int = Path(description="My descripton"),
	debug: bool = Query(default=False, description="some description"),
):
"""

@app.get("/restaurants")
def get_restaurants():
	data_file_path = "restaurants.json"

	with open(data_file_path) as f:
		raw_data = json.load(f)

	return raw_data