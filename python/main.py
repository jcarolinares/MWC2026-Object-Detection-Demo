# Example based on the Object Detection demo by Arduino INC
# Created by Julián Caro Linares for Arduino INC jcarolinares@gmail.com
# CC-BY-SA

from arduino.app_utils import *
from arduino.app_bricks.web_ui import WebUI
from arduino.app_bricks.video_objectdetection import VideoObjectDetection
from datetime import datetime, UTC
import time

cell_phone = False
bottle = False
peace = False

ui = WebUI()
detection_stream = VideoObjectDetection(confidence=0.5, debounce_sec=0.0)

ui.on_message("override_th", lambda sid, threshold: detection_stream.override_threshold(threshold))

# Register a callback for when all objects are detected
def send_detections_to_ui(detections: dict):
  global cell_phone
  for key, values in detections.items():
    for value in values:
      entry = {
        "content": key,
        "confidence": value.get("confidence"),
        "timestamp": datetime.now(UTC).isoformat()
      }
      if key == "cell phone":
          #print("CELL PHONE DETECTED")
          time.sleep(0.2)
          cell_phone = True
          Bridge.call("set_cell_phone", cell_phone)
          cell_phone = False;
      if key == "bottle":
          #print("BOTTLE DETECTED")
          time.sleep(0.2)
          bottle = True
          Bridge.call("set_bottle", bottle)
          bottle = False;
      if key == "peace":
          #print("PEACE")
          time.sleep(0.2)
          peace = True
          Bridge.call("set_peace", peace)
          peace = False;
      ui.send_message("detection", message=entry)

detection_stream.on_detect_all(send_detections_to_ui)

App.run()




