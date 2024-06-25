from django.urls import path
from .views import receive_data, display_data, get_latest_data

urlpatterns = [
    path('receive/', receive_data, name='receive_data'),
    path('display/', display_data, name='display_data'),
    path('latest/', get_latest_data, name='get_latest_data'),
]