from django.shortcuts import render
from .forms import StudentForm, PromotionEligibilityForm
from datetime import date

# ===== Q1: Student Form View =====
def student_form_view(request):
    student_details = None
    percentage = None
    
    if request.method == 'POST':
        form = StudentForm(request.POST)
        if form.is_valid():
            # Get cleaned data
            data = form.cleaned_data
            
            # Calculate percentage
            total_marks = (data['english_marks'] + 
                          data['physics_marks'] + 
                          data['chemistry_marks'])
            percentage = (total_marks / 300) * 100
            
            # Format student details for textarea
            student_details = f"""
Name: {data['name']}
Date of Birth: {data['date_of_birth']}
Address: {data['address']}
Contact Number: {data['contact_number']}
Email ID: {data['email_id']}
English Marks: {data['english_marks']}
Physics Marks: {data['physics_marks']}
Chemistry Marks: {data['chemistry_marks']}
Total Marks: {total_marks}/300
Percentage: {percentage:.2f}%
            """.strip()
    else:
        form = StudentForm()
    
    context = {
        'form': form,
        'student_details': student_details,
        'percentage': percentage
    }
    
    return render(request, 'student_app/student_form.html', context)


# ===== Q2: Promotion Eligibility View =====
def promotion_eligibility_view(request):
    result = None
    years_of_experience = None
    employee_id = None
    
    if request.method == 'POST':
        form = PromotionEligibilityForm(request.POST)
        if form.is_valid():
            # Get cleaned data
            employee_id = form.cleaned_data['employee_id']
            
            # Calculate years of experience
            years_of_experience = form.calculate_experience()
            
            # Check eligibility (more than 5 years)
            if years_of_experience > 5:
                result = "YES"
            else:
                result = "NO"
    else:
        form = PromotionEligibilityForm()
    
    context = {
        'form': form,
        'result': result,
        'years_of_experience': years_of_experience,
        'employee_id': employee_id
    }
    
    return render(request, 'student_app/promotion_form.html', context)