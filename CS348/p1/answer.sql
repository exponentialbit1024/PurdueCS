-- Query 1
SELECT DISTINCT s.s_id S_ID, s.name Name FROM (((student s INNER JOIN takes t ON s.s_id = t.s_id) INNER JOIN teaches tc ON tc.course_id = t.course_id AND tc.sec_id = t.sec_id AND tc.semester = t.semester AND tc.year = t.year) INNER JOIN instructor i on i.i_id = tc.i_id) WHERE i.name = 'Katz' ORDER BY s.name ASC;

-- Query 2
SELECT DISTINCT s_id S_ID, ROUND(SUM(credits * points) / SUM(credits), 2) GradePointAverage FROM (takes NATURAL JOIN course) NATURAL JOIN grade_points GROUP BY s_id ORDER BY GradePointAverage DESC;

-- Query 3
SELECT course_id, sec_id, COUNT(s_id) enrollment FROM takes WHERE semester = 'Fall' AND year = '2009' GROUP BY (course_id, sec_id) ORDER BY enrollment DESC;

-- Query 4
SELECT course_id, sec_id FROM takes WHERE semester = 'Fall' AND year = '2009' HAVING COUNT(s_id) = (SELECT MAX(enrollement) FROM (SELECT course_id, sec_id, count(s_id) enrollement FROM section NATURAL JOIN takes WHERE semester = 'Fall' AND year = '2009' GROUP BY (course_id, sec_id))) GROUP BY (course_id, sec_id) ORDER BY course_id ASC;

-- Query 5
select name InstructorName, sum(c) NumberOfCoursesTaught from (select name, count(name) c from (select distinct t.i_id, i.name name, t.course_id course, t.semester sem, t.year year from (teaches t inner join instructor i on t.i_id = i.i_id) group by t.course_id, t.sec_id, t.semester, t.year, i.name, t.i_id) group by name, course, sem, year) group by name order by sum(c) desc, name offset 0 rows fetch next 4 rows only;

-- Query 6
SELECT semester, year, COUNT(course_id) NumberOfCourses FROM section group by year,semester order by NumberOfCourses desc offset 0 rows fetch next 3 rows only;

-- Query 7
SELECT t.s_id S_ID, s.name StudentName, COUNT(s.name) NumberOfCourses FROM (takes t INNER JOIN student s ON s.s_id = t.s_id) GROUP BY t.s_id, s.name ORDER BY NumberOfCourses DESC OFFSET 0 ROWS FETCH NEXT 2 ROWS ONLY;

-- Query 8
select name InstructorName, sum(enrolc) TotalEnrollment FROM (select i.name, count(distinct s_id) enrolc from (takes t inner join (instructor i inner join teaches tc on i.i_id = tc.i_id) on tc.course_id = t.course_id AND tc.semester = t.semester AND tc.year = t.year AND tc.sec_id = t.sec_id) group by i.name, t.course_id) group by name order by sum(enrolc) desc offset 0 rows fetch next 4 rows only; 

-- Query 9
SELECT DISTINCT dept_name, course_id FROM Course WHERE dept_name = 'Comp. Sci.' OR dept_name = 'History'order by course_id asc;

-- Query 10
select cp.course_id, cp.dept_name, c.course_id, c.dept_name from (course c inner join (course cp inner join prereq pp on cp.course_id = pp.course_id) on c.course_id = pp.prereq_id) where c.dept_name != cp.dept_name order by cp.course_id;
