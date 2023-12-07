from bs4 import BeautifulSoup

# Read the HTML file
with open('./raw_page.html', 'r', encoding='utf-8') as file:
    html_content = file.read()

# Parse HTML content using the 'lxml' parser
soup = BeautifulSoup(html_content, 'lxml')

# Find the table
table = soup.find('table')

# Extract table data
rows = table.find_all('tr')

# Initialize CSV content
csv_content = ''

for row in rows:
    cols = row.find_all(['td', 'th'])
    row_data = [col.get_text(strip=True) for col in cols]
    csv_content += ','.join(row_data) + '\n'

# Write the CSV content to a file
with open('./raw_data.csv', 'w', encoding='utf-8-sig') as csv_file:
    csv_file.write(csv_content)
