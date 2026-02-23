from django.urls import path
from . import views

urlpatterns = [
    path('', views.home_view, name='book_home'),
    path('metadata/', views.metadata_view, name='metadata'),
    path('reviews/', views.reviews_view, name='reviews'),
    path('publisher/', views.publisher_view, name='publisher'),
]