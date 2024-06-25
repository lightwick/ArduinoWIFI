from django.shortcuts import render

from django.http import JsonResponse
from django.views.decorators.csrf import csrf_exempt
from .models import SensorData

@csrf_exempt
def receive_data(request):
    if request.method == 'POST':
        state = request.POST.get('state')
        if state is not None:
            SensorData.objects.create(data=float(state))  # Store the button state
            return JsonResponse({'status': 'success'})
        return JsonResponse({'status': 'failed', 'reason': 'no state'})
    return JsonResponse({'status': 'failed', 'reason': 'invalid method'})

def display_data(request):
    data = SensorData.objects.all().order_by('-timestamp')[:10]  # Fetch last 10 entries
    return render(request, 'wifi/display_data.html', {'data': data})

def get_latest_data(request):
    latest_data = SensorData.objects.order_by('-timestamp').first()
    data = {
        'timestamp': latest_data.timestamp,
        'data': latest_data.data,
    }
    return JsonResponse(data)
