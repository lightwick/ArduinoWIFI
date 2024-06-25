from django.db import models

class SensorData(models.Model):
    timestamp = models.DateTimeField(auto_now_add=True)
    data = models.FloatField()

    def __str__(self):
        return f"{self.timestamp}: {self.data}"