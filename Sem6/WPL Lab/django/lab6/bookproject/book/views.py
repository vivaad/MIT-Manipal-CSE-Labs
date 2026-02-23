from django.shortcuts import render

def home_view(request):
    return render(request, 'book/home.html')

def metadata_view(request):
    return render(request, 'book/metadata.html')

def reviews_view(request):
    return render(request, 'book/reviews.html')

def publisher_view(request):
    return render(request, 'book/publisher.html')