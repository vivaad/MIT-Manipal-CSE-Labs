from django.urls import path
from . import views

urlpatterns = [
    path('', views.student_form_view, name='student_form'),
    path('promotion/', views.promotion_eligibility_view, name='promotion_eligibility'),
]