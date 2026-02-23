from django import forms
from datetime import date

# ===== Q1: Student Form =====
class StudentForm(forms.Form):
    name = forms.CharField(
        max_length=100,
        widget=forms.TextInput(attrs={'class': 'form-control', 'placeholder': 'Enter student name'})
    )
    date_of_birth = forms.DateField(
        widget=forms.DateInput(attrs={'class': 'form-control', 'type': 'date'})
    )
    address = forms.CharField(
        widget=forms.Textarea(attrs={'class': 'form-control', 'rows': 3, 'placeholder': 'Enter address'})
    )
    contact_number = forms.CharField(
        max_length=15,
        widget=forms.TextInput(attrs={'class': 'form-control', 'placeholder': 'Enter contact number'})
    )
    email_id = forms.EmailField(
        widget=forms.EmailInput(attrs={'class': 'form-control', 'placeholder': 'Enter email'})
    )
    english_marks = forms.IntegerField(
        min_value=0,
        max_value=100,
        widget=forms.NumberInput(attrs={'class': 'form-control', 'placeholder': 'Marks (0-100)'})
    )
    physics_marks = forms.IntegerField(
        min_value=0,
        max_value=100,
        widget=forms.NumberInput(attrs={'class': 'form-control', 'placeholder': 'Marks (0-100)'})
    )
    chemistry_marks = forms.IntegerField(
        min_value=0,
        max_value=100,
        widget=forms.NumberInput(attrs={'class': 'form-control', 'placeholder': 'Marks (0-100)'})
    )


# ===== Q2: Promotion Eligibility Form =====
# Sample employee data (you can replace this with database data)
EMPLOYEE_CHOICES = [
    ('', 'Select Employee ID'),
    ('EMP001', 'EMP001'),
    ('EMP002', 'EMP002'),
    ('EMP003', 'EMP003'),
    ('EMP004', 'EMP004'),
    ('EMP005', 'EMP005'),
    ('EMP006', 'EMP006'),
    ('EMP007', 'EMP007'),
    ('EMP008', 'EMP008'),
    ('EMP009', 'EMP009'),
    ('EMP010', 'EMP010'),
]

class PromotionEligibilityForm(forms.Form):
    employee_id = forms.ChoiceField(
        choices=EMPLOYEE_CHOICES,
        widget=forms.Select(attrs={'class': 'form-control'})
    )
    date_of_joining = forms.DateField(
        widget=forms.DateInput(attrs={'class': 'form-control', 'type': 'date'})
    )
    
    def calculate_experience(self):
        """Calculate years of experience"""
        if self.is_valid():
            doj = self.cleaned_data['date_of_joining']
            today = date.today()
            years = today.year - doj.year
            
            # Adjust if birthday hasn't occurred this year
            if (today.month, today.day) < (doj.month, doj.day):
                years -= 1
            
            return years
        return 0